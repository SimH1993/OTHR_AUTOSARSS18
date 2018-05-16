#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

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
DeclareTask(Display);

int direction=1;

void myPrintln(const char *s)
{
 static int y = 0;
 display_goto_xy(0,y);
 display_string(s);
 display_update();
 y++;
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

void WritePort_ReverseDir(int newDir){
	direction=newDir;
}

void WriteTriggerPort_ReverseDir(){
	SetEvent(Display, show);
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

TASK(Display){
	while(1){
		WaitTriggerPort_ReverseDir();
		display_goto_xy(0,0);
		if(ReadPort_ReverseDir()<0){
			display_string("backwards");
		}else{
			display_string("forwards ");
		}
		display_update(); 
	}
	TerminateTask();
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
