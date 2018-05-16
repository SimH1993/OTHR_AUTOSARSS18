#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

DeclareEvent(EvtSignalDrive);
DeclareEvent(EvtSignalReverse);
DeclareEvent(EvtSignalDisp);

DeclareCounter(CounterOne);
DeclareAlarm(AlarmOne);
DeclareAlarm(AlarmTwo);

DeclareTask(PollLeft);
DeclareTask(PollRight);
DeclareTask(TaskDrive);
DeclareTask(TaskReverse);
DeclareTask(TaskDisp);

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int logLineCnt = 7;
int sensOldTouch1State = 0, sensOldTouch2State = 0;
int dirSpeed = 35;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}

void add_log(char *szLog)
{
	if(logLineCnt >= 7)
	{
		display_clear(0);
		display_goto_xy(0, 0);
		logLineCnt = 0;
	}
	
	display_string(szLog);
	display_update();
	logLineCnt++;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


int ReadPort_dir()
{
	return dirSpeed;
}

void WritePort_dir(int val)
{
	dirSpeed = val;
}

void WaitTriggerPort_dir()
{
	WaitEvent(EvtSignalDisp);
}

void WriteTriggerPort_dir()
{
	SetEvent(TaskDisp, EvtSignalDisp);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

TASK(PollLeft)
{
	int sensTouch1State = ecrobot_get_touch_sensor(NXT_PORT_S1);
	
	if(sensTouch1State && !sensOldTouch1State)
		SetEvent(TaskDrive, EvtSignalDrive);
	
	sensOldTouch1State = sensTouch1State;
	
	TerminateTask();
}

TASK(PollRight)
{
	int sensTouch2State = ecrobot_get_touch_sensor(NXT_PORT_S2);
	
	if(sensTouch2State && !sensOldTouch2State)
		SetEvent(TaskReverse, EvtSignalReverse);
	
	sensOldTouch2State = sensTouch2State;
	
	TerminateTask();
}

TASK(TaskDrive)
{
	WaitEvent(EvtSignalDrive);
	
	int dir = ReadPort_dir();
	
	ecrobot_set_motor_speed(NXT_PORT_A, dir);
	ecrobot_set_motor_speed(NXT_PORT_C, dir);
	systick_wait_ms(1000);
	ecrobot_set_motor_speed(NXT_PORT_A, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
	
	ChainTask(TaskDrive);
}

TASK(TaskReverse)
{
	WaitEvent(EvtSignalReverse);
	
	WritePort_dir(-ReadPort_dir());
	
	SetEvent(TaskDisp, EvtSignalDisp);
	
	ChainTask(TaskReverse);
}

TASK(TaskDisp)
{
	WaitEvent(EvtSignalDisp);
	
	add_log(ReadPort_dir() > 0 ? "Vorwaerts\n" : "Rueckwaerts\n");
	
	ChainTask(TaskDisp);
}
