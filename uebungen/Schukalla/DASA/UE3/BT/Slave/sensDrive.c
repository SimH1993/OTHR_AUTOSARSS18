#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

DeclareEvent(EvtSignalDisp);

DeclareCounter(CounterOne);

DeclareTask(Main);
DeclareTask(TaskDisp);

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int logLineCnt = 7;
int sensOldTouch1State = 0, sensOldTouch2State = 0;
int dirSpeed = 35;
int btInitialized = 0;

U8 szBuff[32];

typedef struct
{
	U16 evtId;
	U16 len;
	char data[1];
} NET_HEADER;

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

//TODO: while loop
U8 WaitTriggerPort_dir()
{
	U32 len = ecrobot_read_bt_packet(szBuff, sizeof(szBuff));
	if(len != 0)
	{
		if(*(U8*)(&szBuff[0]) == 0)
			WritePort_dir(*(U8*)(&szBuff[1]);
	}
	
	return len;
}

void WriteTriggerPort_dir()
{
	//Not implemented on slave
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

TASK(Main)
{
	add_log("Waiting for connection...\n");
	
	while(ecrobot_get_bt_status() != BT_STREAM)
		ecrobot_init_bt_slave("AUTOSAR_VL");
	
	add_log("Successfully connected!\n");
	
	TerminateTask();
}

TASK(TaskDisp)
{
	if(WaitTriggerPort_dir())
	{
		add_log(ReadPort_dir() > 0 ? "Vorwaerts\n" : "Rueckwaerts\n");
	}
	
	systick_wait_ms(1000);
	
	ChainTask(TaskDisp);
}
