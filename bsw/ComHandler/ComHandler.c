//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "ComHandler.h"
#include "../Utility/Utility.h"



//Globals
U8 com_initialized = 0;

//Ringbuffer is not really useful for sending since we want to send everything on triggering anyways, so lets just use an array
U16 com_send_len = 0;
U8 com_send_buff[COM_BUFF_SIZE];

//Ringbuffer is used for receiving data since we dont always want to read all available data from the buffer
U16 com_recv_pos = 0, com_recv_len = 0;
U8 com_recv_buff[COM_BUFF_SIZE];

U8 tmp_buff[126];


//Declares
DeclareCounter(CounterOne);

DeclareTask(ComTask_send);
DeclareTask(ComTask_receive);

DeclareEvent(ComEvent_send);
DeclareAlarm(ComAlarm_receive);


//Basic exported functions
U8 com_init(U8 is_master)
{
	if(com_initialized)
		return 1;
	
	SINT status;
	for(int i = 0; (status = ecrobot_get_bt_status()) != BT_STREAM && i < (COM_CONNECT_TIMEOUT / 100); i++)
	{
		if(is_master)
			ecrobot_init_bt_master(com_slave_addr, COM_CONNECT_PASSWD);
		else
			ecrobot_init_bt_slave(COM_CONNECT_PASSWD);
		
		systick_wait_ms(100);
	}
	
	if(status == BT_STREAM)
	{
		com_initialized = 1;
		
		ActivateTask(ComTask_send); //This can also be replaced with an alarm to send at a fixed interval instead of sending each packet separately
		SetRelAlarm(ComAlarm_receive, 1, COM_RECEIVE_SPEED);
		
		return 1;
	}
	
	return 0;
}

U32 com_send(U8 *buff, U32 len)
{
	if(!com_initialized)
		return 0;
	
	DisableAllInterrupts();
	
	U32 ret = 0;
	if(com_send_len + len <= COM_BUFF_SIZE)
	{
		memcpy(com_send_buff + com_send_len, buff, len);
		com_send_len += len;
		
		ret = len;
	}
	
	EnableAllInterrupts();
	
	if(ret)
		SetEvent(ComTask_send, ComEvent_send);
	
	return ret;
}

U8 com_send_packet(U8 id, U8 flags, int data)
{
	U8 buffer[sizeof(header) + sizeof(int)];
	BT_NET_HEADER *header = (BT_NET_HEADER*)buffer;
	
	header->id = id;
	header->flags = flags;
	*(int*)(buffer + sizeof(header)) = data;
	
	U32 sent = 0;
	while(sent < sizeof(buffer))
	{
		U32 len = com_send(buffer + sent, sizeof(buffer) - sent);
		if(!len)
			return 0;
		
		sent += len;
	}
	
	return 1;
}

U32 com_recv(U8 *buff, U32 len)
{
	if(!com_initialized)
		return 0;
	
	DisableAllInterrupts();
	
	U32 trunc_len = len < com_recv_len ? len : com_recv_len;
	
	U32 i;
	for(i = 0; i < trunc_len; i++)
		buff[i] = com_recv_buff[(com_recv_pos + i) % COM_BUFF_SIZE];
	
	com_recv_pos = (com_recv_pos + trunc_len) % COM_BUFF_SIZE;
	com_recv_len -= trunc_len;
	
	EnableAllInterrupts();
	
	return trunc_len;
}

void com_terminate()
{
	if(!com_initialized)
		return;
	
	com_initialized = 0;
	SetEvent(ComTask_send, ComEvent_send);
	CancelAlarm(ComAlarm_receive);
	
	systick_wait_ms(100);
	
	ecrobot_term_bt_connection();
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//Private functions and tasks


//Hooks -> have to be moved later
void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}



//Send task, non preemp to avoid usage of locks/disabling irqs
//Waits for a user event to be triggered, event is triggered by 'com_send' calls
TASK(ComTask_send)
{
	while(com_initialized)
	{
		WaitEvent(ComEvent_send);
		ClearEvent(ComEvent_send);
		if(!com_initialized)
			break;
		
		while(com_send_len > 0)
			com_send_len -= ecrobot_send_bt_packet(com_send_buff, com_send_len >= 254 ? 254 : com_send_len);
	}
	
	TerminateTask();
}


//Receive task, non preemp to avoid usage of locks/disabling irqs
//Waits for a timer interrupt, gets triggered each 33ms (see COM_RECEIVE_SPEED) by an alarm to poll for incoming data
TASK(ComTask_receive)
{
	while(com_recv_len < COM_BUFF_SIZE)
	{
		U32 left_len = COM_BUFF_SIZE - com_recv_len;
		if(left_len > 126)
			left_len = 126;
		
		U32 len = ecrobot_read_bt_packet(tmp_buff, left_len);
		if(!len)
			break;
		
		U32 i;
		for(i = 0; i < len; i++)
			com_recv_buff[(com_recv_pos + com_recv_len + i) % COM_BUFF_SIZE] = tmp_buff[i];
		
		com_recv_len += len;
	}
	
	//Merged from runnable_bt_dispatcher
	//Only 1 single int data now (fixed length)
	U32 received = 0;
	BT_NET_HEADER header;
	
	while(received < sizeof(header))
	{
		U32 len = com_recv((U8*)header + received, sizeof(header) - received);
		if(!len)
			return;
		
		received += len;
	}
	
	received = 0;
	while(received < sizeof(int))
	{
		U32 len = com_recv(dataBuff + received, sizeof(int) - received);
		if(!len)
			return;
		
		received += len;
	}
	
	rte_set_data(header.id, *(int*)dataBuff);
	
	TerminateTask();
}
