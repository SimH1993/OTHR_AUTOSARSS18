#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#define RTE_ADC_READ_JoystickTaster()	ADC_Read_Value(0, NXT_PORT_S4, 0x48, 2)
#define RTE_ADC_READ_JostickHorizontal()	ADC_Read_Value(0, NXT_PORT_S4, 0x48, 0)
#define RTE_ADC_READ_JoystickVertical()	ADC_Read_Value(0, NXT_PORT_S4, 0x48, 1)
#define RTE_WRITE_OutJoystickHorizontal(value) localSenderReceiver[0] = value
#define RTE_WRITE_OutUltraschall(value) localSenderReceiver[2] = value
#define RTE_TRIGGER_OutFlankenerkennung() com_send_packet(0, 0, 1)
#define RTE_ECR_ULTRASCHALL_READ_Ultraschall()	sonar_read_distance(NXT_PORT_S2)
#define RTE_ADC_READ_BlinkerTaster()	ADC_Read_Value(1, NXT_PORT_S1, 0, 0)
#define RTE_WRITE_OutJoystickTaster(value) localSenderReceiver[1] = value
#define RTE_WRITE_OutJoystickVertical(value) localSenderReceiver[3] = value


#include "..\runnables\Runnable_JoystickAuslesen.c"
#include "..\runnables\Runnable_UltraschallAuslesen.c"
#include "..\runnables\Runnable_FlankenErkennung.c"


TASK(SWC_1_Main){

	EventMaskType taskEvents;
	
	while(1){
	
		WaitEvent(TriggerJoystickAuslesen | TriggerUltraschallAuslesen | TriggerFlankenErkennung);

		GetEvent(SWC_1_Main, &taskEvents);
		if ( taskEvents & TriggerJoystickAuslesen ) {
	// Call runnable
	runnable_JoystickAuslesen();
	ClearEvent(TriggerJoystickAuslesen);
}

if ( taskEvents & TriggerUltraschallAuslesen ) {
	// Call runnable
	runnable_UltraschallAuslesen();
	ClearEvent(TriggerUltraschallAuslesen);
}

if ( taskEvents & TriggerFlankenErkennung ) {
	// Call runnable
	runnable_FlankenErkennung();
	ClearEvent(TriggerFlankenErkennung);
}


	}
	TerminateTask();
}


