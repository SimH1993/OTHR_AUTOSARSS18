#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#define PORT_DIRECTION 2
#define PORT_SHOW 1

DeclareEvent(right_taster);
DeclareEvent(left_taster);
DeclareEvent(show);
DeclareCounter(Timer1);
DeclareAlarm(Alarm1);
DeclareAlarm(Alarm2);

DeclareTask(CheckLeft); 
DeclareTask(CheckRight);
DeclareTask(ReverseDir);
DeclareTask(Drive);

signed char direction=1;

void ecrobot_device_initialize()
{
	char slaveAddr[7] = {0,22,83,17,45,26,0}; //bot
	//U8 slaveAddr[7] = {0x58,0xc5,0xcb, 0xb7, 0xde, 0xba, 0x00};	//phone
	ecrobot_init_bt_master(slaveAddr, "Autosar_VL");
}

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

signed char data[2];
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

void WritePort_ReverseDir(int newDir){
	direction=newDir;
	//data={direction}
	U8 data_dir[2];
	data_dir[0] = PORT_DIRECTION;
	data_dir[1]= direction;
	U32 res=ecrobot_send_bt_packet((void*)data_dir, sizeof(data_dir));
	if(res){
		myPrintln("sent DIR");
	}
	//myPrintln("sent DIR");
}

void WriteTriggerPort_ReverseDir(){
	//SetEvent(Display, show);
	//port 0, data 1 --> 0x0001
	U8 data_show[2];
	data_show[0] = PORT_SHOW;
	data_show[1]=1;
	U32 res=ecrobot_send_bt_packet((void*)data_show, sizeof(data_show));
	if(res){
		myPrintln("sent SHOW");
	}
	//myPrintln("sent SHOW");
}

void WriteTriggerPort_PollRight(){
	SetEvent(Drive, right_taster);
}

void WriteTriggerPort_PollLeft(){
	SetEvent(ReverseDir, left_taster);
}

void WaitTriggerPort_PollRight(){
	WaitEvent(right_taster);
	ClearEvent(right_taster);
}

void WaitTriggerPort_PollLeft(){
	WaitEvent(left_taster);
	ClearEvent(left_taster);
}

void WaitTriggerPort_ReverseDir(){
	WaitEvent(show);
	ClearEvent(show);
}

TASK(ReverseDir){
	while(1){
		WaitTriggerPort_PollLeft();
		WritePort_ReverseDir(ReadPort_ReverseDir()*-1);
		
		WriteTriggerPort_ReverseDir();
	}
	TerminateTask();
}

TASK(Drive)
{
	int speed=35;
	while(1){
		WaitTriggerPort_PollRight();
		int dir=ReadPort_ReverseDir();
		ecrobot_set_motor_speed(NXT_PORT_A,speed*dir);
		ecrobot_set_motor_speed(NXT_PORT_C,speed*dir);
		systick_wait_ms(1000);
		ecrobot_set_motor_speed(NXT_PORT_A,0);
		ecrobot_set_motor_speed(NXT_PORT_C,0);
	}
	TerminateTask(); /* Task beenden */
} 

TASK(CheckRight){
	static int was_last_pressed = 0;
	if(ecrobot_get_touch_sensor(NXT_PORT_S1) && !was_last_pressed){
		WriteTriggerPort_PollRight();
		was_last_pressed = 1;
	} else if (!ecrobot_get_touch_sensor(NXT_PORT_S1) && was_last_pressed) {
		was_last_pressed = 0;
	}
	TerminateTask();
}

TASK(CheckLeft){
	static int was_last_pressed = 0;
	if(ecrobot_get_touch_sensor(NXT_PORT_S4) && !was_last_pressed){
		WriteTriggerPort_PollLeft();
		was_last_pressed = 1;
	} else if (!ecrobot_get_touch_sensor(NXT_PORT_S4) && was_last_pressed) {
		was_last_pressed = 0;
	}
	TerminateTask();
};
