#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//GENERATED
#define RTE_READ_InJoystickSound() localSenderReceiver[1]
//GENERATED
#define RTE_READ_InUltraschall() localSenderReceiver[2]


#include "..\runnables\Runnable_DisplayAusgabe.c"
#include "..\runnables\Runnable_SoundAusgabe.c"


TASK(SWC_4_Main){

	EventMaskType taskEvents;
	
	while(1){
	
		WaitEvent(TriggerDisplayAusgabe | TriggerSoundAusgabe);

		GetEvent(SWC_4_Main, &taskEvents);
		if ( taskEvents & TriggerDisplayAusgabe ) {
	// Call runnable
	runnable_DisplayAusgabe();
	ClearEvent(TriggerDisplayAusgabe);
}

if ( taskEvents & TriggerSoundAusgabe ) {
	// Call runnable
	runnable_SoundAusgabe();
	ClearEvent(TriggerSoundAusgabe);
}


	}
	TerminateTask();
}


