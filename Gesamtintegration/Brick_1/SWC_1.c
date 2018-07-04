#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#define RTE_ADC_READ_JOYSTICKX()  		ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0)
#define RTE_ADC_READ_JOYSTICKY()  		ADC_Read_Value(1, NXT_PORT_S4, 0x48, 1)
#define RTE_ADC_READ_JOYSTICKBUTTON()  	ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2)

#define RTE_JOYSTICK_X_WRITE(value) localSenderReceiver[0] = value;
#define RTE_JOYSTICK_Y_WRITE(value) localSenderReceiver[1] = value;
#define RTE_JOYSTICK_TASTER_WRITE(value) localSenderReceiver[2] = value;



#include "../runnables/runnable_joystick.c"
#include "../runnables/runnable_sonar.c"
#include "../runnables/runnable_edge_detection.c"

TASK(SWC_1_Main){

	EventMaskRefType taskEvents;
	
	while(1){
	
		WaitEvent(TriggerJoystickAuslesen | TriggerUltraschallAuslesen | TriggerFlankenErkennung);

		GetEvent(SWC_1_Main, taskEvents);
		if ( *taskEvents & TriggerJoystickAuslesen ) {
		// Call runnable
			runnable_joystick();
			ClearEvent(TriggerJoystickAuslesen);
		}

		if ( *taskEvents & TriggerUltraschallAuslesen ) {
			// Call runnable
			runnable_sonar();
			ClearEvent(TriggerUltraschallAuslesen);
		}

		if ( *taskEvents & TriggerFlankenErkennung ) {
			// Call runnable
			runnable_edge_detection();
			ClearEvent(TriggerFlankenErkennung);
		}
	}
	TerminateTask();
}


