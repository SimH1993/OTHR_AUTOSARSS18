#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 
#include "SWC_2_Runnable_WerteBerechnen.c"


<DECLARES>

//GENERATED
int Rte_Read_InJoystick(){
	return localSenderReceiver[0];
}

//GENERATED
void Rte_Write_OutMotorspeed(int value){
	<FUNCTION_BODY>
}

//GENERATED
int Rte_Read_InMotorRPM(){
	<FUNCTION_BODY>
}


