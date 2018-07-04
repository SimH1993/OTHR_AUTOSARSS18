#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//GENERATED
int Rte_Read_InJoystick(){
	return localSenderReceiver[0];
}

//GENERATED
void Rte_Write_OutMotorspeed(int value){
	//<FUNCTION_BODY>
}

//GENERATED
int Rte_Read_InMotorRPM(){
	//<FUNCTION_BODY>
}



// #include "SWC_2_Runnable_WerteBerechnen.c"
#include "../runnables/runnable_calculater.c"


TASK(SWC_2_Main){

	int taskEvents;
	
	while(1){
	
		WaitEvent(TriggerWerteBerechnen);

		GetEvent(SWC_2_Main, &taskEvents);
		if ( taskEvents & TriggerWerteBerechnen ) {
	// Call runnable
	SWC_2_Runnable_WerteBerechnen();
	ClearEvent(TriggerWerteBerechnen);
}


	}
	TerminateTask();
}


