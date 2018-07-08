//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 
#include "../BSW/SoundHandler/SoundHandler.h"

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
DeclareEvent(ComEvent_receive);
DeclareAlarm(ComAlarm_receive);


//Basic exported functions
U8 com_init()
{
	if(com_initialized)
		return 1;
	
	SINT status;
	for(int i = 0; (status = ecrobot_get_bt_status()) != BT_STREAM && i < (COM_CONNECT_TIMEOUT / 100); i++)
	{
		if (btIsmaster == 1){
			ecrobot_init_bt_master(com_slave_addr, COM_CONNECT_PASSWD);
		} else {
			ecrobot_init_bt_slave(COM_CONNECT_PASSWD);
		}
		systick_wait_ms(100);
	}
	
	if(status == BT_STREAM)
	{
		
		play_single_tone(1000, 300, 50);
		
		com_initialized = 1;
		// Now done automatically in the oil
		// ActivateTask(ComTask_send); //This can also be replaced with an alarm to send at a fixed interval instead of sending each packet separately
		// CancelAlarm(ComAlarm_receive);
		// SetRelAlarm(ComAlarm_receive, 100, 33);
		
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
	
	if(ret) {
		SetEvent(ComTask_send, ComEvent_send);
	}
	
	return ret;
}

U8 com_send_packet(U8 id, U8 flags, int data)
{
	U8 buffer[sizeof(BT_NET_HEADER) + sizeof(int)];
	BT_NET_HEADER *header = (BT_NET_HEADER*)buffer;
	
	header->id = id;
	header->flags = flags;
	buffer[0] = id;
	buffer[1] = flags;
	*(int*)(buffer + sizeof(BT_NET_HEADER)) = data;
	
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
		{
			if(com_send_len >= 254)
			{	
				ecrobot_send_bt_packet(com_send_buff, 254);
				com_send_len -= 254;
			}
			else
			{
				//U32 len = ecrobot_send_bt_packet(com_send_buff, com_send_len);
				ecrobot_send_bt_packet(com_send_buff, com_send_len);
				display_goto_xy(0,0);
				display_unsigned(com_send_buff[0], 6);
				display_goto_xy(0,1);
				display_unsigned(com_send_buff[1], 6);
				display_goto_xy(0,2);
				display_unsigned(com_send_buff[2], 6);
				display_goto_xy(0,3);
				display_unsigned(com_send_buff[3], 6);
				display_goto_xy(0,4);
				display_unsigned(com_send_buff[4], 6);
				display_goto_xy(0,5);
				display_unsigned(com_send_buff[5], 6);
				display_goto_xy(0,6);
				display_unsigned(com_send_buff[6], 6);
				display_goto_xy(0,7);
				display_unsigned(com_send_buff[7], 6);
				display_update();
				com_send_len = 0;
			}
		}
	}
	
	TerminateTask();
}


//Receive task, non preemp to avoid usage of locks/disabling irqs
//Waits for a timer interrupt, gets triggered each 33ms (see COM_RECEIVE_SPEED) by an alarm to poll for incoming data
TASK(ComTask_receive)
{

	while(1) {
		
		WaitEvent(ComEvent_receive);
		ClearEvent(ComEvent_receive);

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
			
			// display_goto_xy(0,0);
			// display_unsigned(tmp_buff[0], 6);
			// display_goto_xy(0,1);
			// display_unsigned(tmp_buff[1], 6);
			// display_goto_xy(0,2);
			// display_unsigned(tmp_buff[2], 6);
			// display_goto_xy(0,3);
			// display_unsigned(tmp_buff[3], 6);
			// display_goto_xy(0,4);
			// display_unsigned(tmp_buff[4], 6);
			// display_goto_xy(0,5);
			// display_unsigned(tmp_buff[5], 6);
			// display_goto_xy(0,6);
			// display_unsigned(tmp_buff[6], 6);
			// display_goto_xy(0,7);
			// display_unsigned(tmp_buff[7], 6);
			// display_update();
			
		}
		
		// display_goto_xy(0,0);
		// display_unsigned(com_recv_len, 6);
		// display_update();
		
		//Merged from runnable_bt_dispatcher
		//Only 1 single int data now (fixed length)
		U32 received = 0;
		U8 buffer[sizeof(BT_NET_HEADER) + sizeof(int)];
		BT_NET_HEADER *header = (BT_NET_HEADER*)buffer;
		
		U8 breakCondition = 1;
		
		while((received < sizeof(BT_NET_HEADER)) && breakCondition)
		{
			U32 len = com_recv((U8*)buffer + received, sizeof(BT_NET_HEADER));
			if(len == 0){
				breakCondition = 0;
			} else {
				received += len;
			}
		}
		
		received = 0;
		while((received < sizeof(int)) && breakCondition)
		{
			U32 len = com_recv(buffer + received, sizeof(int));
			if(len == 0){
				breakCondition = 0;
			} else {
				received += len;
			}
		}
		
		display_goto_xy(0,0);
		display_unsigned(header->id, 6);
		display_goto_xy(0,1);
		display_int(*buffer, 6);
		display_goto_xy(0,2);
		display_int(*(buffer+1), 6);
		display_update();
		
		rte_set_data(header->id, *(int*)buffer);
		
	}
	
	TerminateTask();
}
