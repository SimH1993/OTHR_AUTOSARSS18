#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

DeclareCounter(a_counter);
DeclareAlarm(an_alarm);
DeclareEvent(evt1);
DeclareEvent(evt2);

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(a_counter);
	if(ercd != E_OK)
		ShutdownOS(ercd);
} 

DeclareTask(Main); 
DeclareTask(One); 


TASK(Main)
{
	display_string("Main started\n");
	display_update();
	
	display_string("Main send evt1\n");
	display_update();
	SetEvent(One, evt1);
	
	display_string("Main send evt2\n");
	display_update();
	SetEvent(One, evt2);
	
	TerminateTask();
}

TASK(One)
{
	display_string("One started\n");
	display_update();
	
	WaitEvent(evt1);
	
	display_string("One rec evt1\n");
	display_update();
	
	
	
	WaitEvent(evt2);
	
	display_string("One rec evt2\n");
	display_update();
	
	TerminateTask();
}
