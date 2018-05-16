#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#define PORT_DIRECTION 2
#define PORT_SHOW 1

DeclareEvent(show);
DeclareEvent(recv);
DeclareCounter(Timer1);
DeclareAlarm(Alarm1);
DeclareTask(Display);
DeclareTask(BT_recv);

signed char direction=1;

void myPrintln(const char *s)
{
 static int y = 0;
 display_goto_xy(0,y);
 display_string("                "); // 16 spaces for clear
 display_goto_xy(0,y);
 display_string(s);
 display_update();
 y++;
 y %= 8;
} 

void user_1ms_isr_type2(void)
{
 StatusType ercd;
 ercd = SignalCounter(Timer1);
 if( ercd != E_OK ){
 ShutdownOS( ercd );
 }
}

int ReadPort_ReverseDir(){
	return direction;
}

void WaitTriggerPort_ReverseDir(){
	WaitEvent(show);
	ClearEvent(show);
}

TASK(BT_recv){
	myPrintln("waiting for master");
	while(ecrobot_get_bt_status() != BT_STREAM)
	{
		ecrobot_init_bt_slave("Autosar_VL");
	}
	myPrintln("connected");
	U32 packet_len=0;
	U8 data[2] = {0,0};
	while(1)
	{	
		WaitEvent(recv);
		ClearEvent(recv);
		packet_len=ecrobot_read_bt_packet((void*)data, 2);
		if(packet_len)
		{
			switch(data[0])
			{
				case PORT_DIRECTION:
					direction = data[1];
					break;
				case PORT_SHOW:
					SetEvent(Display, show);
					break;
				default:
					break;
			}
		}
	}
	TerminateTask();
}

TASK(Display){
	while(1){
		WaitTriggerPort_ReverseDir();
		display_goto_xy(0,0);
		if(ReadPort_ReverseDir()<0){
			display_string("backwards       ");
		}else{
			display_string("forwards        ");
		}
		display_update(); 
	}
	TerminateTask();
}
