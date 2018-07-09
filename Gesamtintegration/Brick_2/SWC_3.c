#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#define RTE_ECR_MOTOR_WRITE_MotorLinks(value)	motor_set_speed(NXT_PORT_A, value)
#define RTE_ECR_MOTOR_WRITE_MotorRechts(value)	motor_set_speed(NXT_PORT_B, value)
#define RTE_DIO_READ_BlinkerLED1()	DIO_Read_Pin(0, NXT_PORT_S1, 0x26, 0)
#define RTE_DIO_WRITE_BlinkerLED1(value)	DIO_Write_Pin(0, NXT_PORT_S1, 0x26, 0, value)
//GENERATED
#define RTE_READ_InMotorspeed() remotePorts[1]
#define RTE_DIO_READ_BlinkerLED2()	DIO_Read_Pin(0, NXT_PORT_S1, 0x26, 1)
#define RTE_DIO_WRITE_BlinkerLED2(value)	DIO_Write_Pin(0, NXT_PORT_S1, 0x26, 1, value)
#define RTE_DIO_READ_BlinkerLED3()	DIO_Read_Pin(0, NXT_PORT_S1, 0x26, 2)
#define RTE_DIO_WRITE_BlinkerLED3(value)	DIO_Write_Pin(0, NXT_PORT_S1, 0x26, 2, value)
#define RTE_DIO_READ_BlinkerLED4()	DIO_Read_Pin(0, NXT_PORT_S1, 0x26, 3)
#define RTE_DIO_WRITE_BlinkerLED4(value)	DIO_Write_Pin(0, NXT_PORT_S1, 0x26, 3, value)


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


