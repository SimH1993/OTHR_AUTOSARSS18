#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#define RTE_ADC_READ_Links()	ADC_Read_Value(0, NXT_PORT_A, 0, 0)
#define RTE_ADC_READ_Rechts()	ADC_Read_Value(0, NXT_PORT_B, 0, 0)
#define RTE_DIO_READ_Blinker()	DIO_Read_Value(0, NXT_PORT_S1, 0x26, 0)
//GENERATED
#define RTE_READ_InMotorspeed() remotePorts[1]


#include "..\runnables\Runnable_Motorsteuerung.c"
#include "..\runnables\Runnable_Blinkersteuerung.c"


TASK(SWC_3_Main){

	EventMaskType taskEvents;
	
	while(1){
	
		WaitEvent(TriggerMotorsteuerung | TriggerBlinkersteuerung);

		GetEvent(SWC_3_Main, &taskEvents);
		if ( taskEvents & TriggerMotorsteuerung ) {
	// Call runnable
	runnable_Motorsteuerung();
	
	// display_goto_xy(0,0);
	// display_int(remotePorts[0], 6);
	// display_goto_xy(0,1);
	// display_int(remotePorts[1], 6);
	// display_update();
	
	if (remotePorts[0]) {
		ecrobot_sound_tone(1000, 100, 50);
	}
	
	ClearEvent(TriggerMotorsteuerung);
}

if ( taskEvents & TriggerBlinkersteuerung ) {
	// Call runnable
	runnable_Blinkersteuerung();
	ClearEvent(TriggerBlinkersteuerung);
}


	}
	TerminateTask();
}
