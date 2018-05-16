#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

void myPrintln(const char *s)
{
 static int y = 0;
 display_goto_xy(0,y);
 display_string(s);
 display_update();
 y++;
} 

DeclareEvent(right_taster);
DeclareEvent(left_taster);
DeclareCounter(Timer1);
DeclareAlarm(Alarm1);
DeclareTask(CheckLeft); 
DeclareTask(CheckRight);
DeclareTask(Main);


void user_1ms_isr_type2(void)
{
 StatusType ercd;
 ercd = SignalCounter(Timer1);
 if( ercd != E_OK ){
 ShutdownOS( ercd );
 }
} 




TASK(Main)
{
	EventMaskType curevent;
	int speed=35;
	while(1){
		WaitEvent(left_taster|right_taster);
		GetEvent(Main, &curevent);
		if(curevent&right_taster){
			speed*=-1;
			ClearEvent(right_taster);
		}else if(curevent&left_taster){
			ecrobot_set_motor_speed(NXT_PORT_A,speed);
			ecrobot_set_motor_speed(NXT_PORT_C,speed);
			systick_wait_ms(1000);
			ecrobot_set_motor_speed(NXT_PORT_A,0);
			ecrobot_set_motor_speed(NXT_PORT_C,0);
			ClearEvent(left_taster);
		}
	}
	TerminateTask(); /* Task beenden */
} 


TASK(CheckRight){
	static int was_last_pressed = 0;
	if(ecrobot_get_touch_sensor(NXT_PORT_S1) && !was_last_pressed){
		SetEvent(Main, right_taster);
		was_last_pressed = 1;
	} else if (!ecrobot_get_touch_sensor(NXT_PORT_S1) && was_last_pressed) {
		was_last_pressed = 0;
	}
	TerminateTask();
}

TASK(CheckLeft){
	ActivateTask(CheckRight);
	if(ecrobot_get_touch_sensor(NXT_PORT_S4)){
		SetEvent(Main, left_taster);
	}
	TerminateTask();
};
