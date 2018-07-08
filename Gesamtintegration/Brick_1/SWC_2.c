#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//GENERATED
#define RTE_READ_InJoystickHorizontal() localSenderReceiver[0]
//GENERATED
#define RTE_READ_InJoystickVertical() localSenderReceiver[3]
#define RTE_WRITE_OutMotorspeed(value) com_send_packet(1, 0, value)


#include "..\runnables\Runnable_WerteBerechnen.c"


TASK(SWC_2_Main){

	EventMaskType taskEvents;
	
	while(1){
	
		WaitEvent(TriggerWerteBerechnen);

		GetEvent(SWC_2_Main, &taskEvents);
		if ( taskEvents & TriggerWerteBerechnen ) {
	// Call runnable
	//runnable_WerteBerechnen();
	ClearEvent(TriggerWerteBerechnen);
}


	}
	TerminateTask();
}


