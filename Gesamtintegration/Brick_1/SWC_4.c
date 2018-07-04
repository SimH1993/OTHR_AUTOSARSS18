#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//GENERATED
int Rte_Read_InJoystickSound(){
	return localSenderReceiver[1];
}

//GENERATED
int Rte_Read_InUltraschall(){
	return localSenderReceiver[2];
}



// #include "SWC_4_Runnable_DisplayAusgabe.c"
// #include "SWC_4_Runnable_SoundAusgabe.c"
#include "../runnables/runnable_display.c"
#include "../runnables/runnable_sound.c"


TASK(SWC_4_Main){

	int taskEvents;
	
	while(1){
	
		WaitEvent(TriggerDisplayAusgabe | TriggerSoundAusgabe);

		GetEvent(SWC_4_Main, &taskEvents);
		if ( taskEvents & TriggerDisplayAusgabe ) {
	// Call runnable
	SWC_4_Runnable_DisplayAusgabe();
	ClearEvent(TriggerDisplayAusgabe);
}

if ( taskEvents & TriggerSoundAusgabe ) {
	// Call runnable
	SWC_4_Runnable_SoundAusgabe();
	ClearEvent(TriggerSoundAusgabe);
}


	}
	TerminateTask();
}


