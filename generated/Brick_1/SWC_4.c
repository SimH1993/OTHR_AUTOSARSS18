#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 


#define RTE_JOYSTICK_X_READ() localSenderReceiver[0]
#define RTE_JOYSTICK_Y_READ() localSenderReceiver[1]
#define RTE_JOYSTICK_BUTTON_READ() localSenderReceiver[2]


#include "SWC_4_Runnable_DisplayAusgabe.c"
#include "SWC_4_Runnable_SoundAusgabe.c"


//<DECLARES>
DeclareTask(SWC_4_Main);

DeclareEvent(evtSWC4_RunnableDisplay);
DeclareEvent(evtSWC4_RunnableSound);

TASK(SWC_4_Main) 
{
	int taskEvents;
	
	while(1){
		
		WaitEvent(evtSWC4_RunnableDisplay|evtSWC4_RunnableSound);
		
		GetEvent(SWC_4_Main, &taskEvents);
		
		if ( taskEvents & evtSWC4_RunnableDisplay ) {
			// Call runnable
			swc_4_DisplayAusgabe();
			ClearEvent(evtSWC4_RunnableDisplay);
		}
		
		if ( taskEvents & evtSWC4_RunnableSound ) {
			// Call runnable
			swc_4_SoundAusgabe();
			ClearEvent(evtSWC4_RunnableSound);
		}
	}
	
	// This should never be called!
	TerminateTask();
 }

// //GENERATED
// int Rte_Read_InJoystickSound(){
	// return localSenderReceiver[1];
// }

// //GENERATED
// int Rte_Read_InUltraschall(){
	// return localSenderReceiver[2];
// }




