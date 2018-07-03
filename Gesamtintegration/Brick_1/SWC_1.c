#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

#include "bsw/ADC/AdcIF.h"

//<DECLARES>
DeclareTask(SWC_1_Main);

DeclareEvent(evtSWC1_RunnableJoystick);
DeclareEvent(evtSWC1_RunnableUltraschall);
DeclareEvent(evtSWC1_RunnableFlankenErkennung);


#define RTE_ADC_READ_JOYSTICKX()  		ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0)
#define RTE_ADC_READ_JOYSTICKY()  		ADC_Read_Value(1, NXT_PORT_S4, 0x48, 1)
#define RTE_ADC_READ_JOYSTICKBUTTON()  	ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2)

#define RTE_JOYSTICK_X_WRITE(value) localSenderReceiver[0] = value;
#define RTE_JOYSTICK_Y_WRITE(value) localSenderReceiver[1] = value;
#define RTE_JOYSTICK_TASTER_WRITE(value) localSenderReceiver[2] = value;

#include "SWC_1_Runnable_JoystickAuslesen.c"
#include "SWC_1_Runnable_UltraschallAuslesen.c"
#include "SWC_1_Runnable_FlankenErkennung.c"


TASK(SWC_1_Main) 
{
	int taskEvents;
	
	while(1){
		WaitEvent(evtSWC1_RunnableJoystick|evtSWC1_RunnableUltraschall|evtSWC1_RunnableFlankenErkennung);
		
		GetEvent(SWC_1_Main, &taskEvents);
		
		if ( taskEvents & evtSWC1_RunnableJoystick ) {
			// Call runnable
			swc_1_JoystickAuslesen();
			ClearEvent(evtSWC1_RunnableJoystick);
		}
		if ( taskEvents & evtSWC1_RunnableUltraschall ) {
			// Call runnable
			swc_1_UltraschallAuslesen();
			ClearEvent(evtSWC1_RunnableUltraschall);
		}
		if ( taskEvents & evtSWC1_RunnableFlankenErkennung ) {
			// Call runnable
			swc_1_FlankenErkennung();
			ClearEvent(evtSWC1_RunnableFlankenErkennung);
		}
	}
	
	// This should never be called!
	TerminateTask();
 }


//GENERATED
// void Rte_Write_OutJoystick(int value){
	// localSenderReceiver[0] = value;
// }

// //GENERATED
// void Rte_Write_OutUltraschall(int value){
	// localSenderReceiver[2] = value;
// }

// //GENERATED
// void Rte_Trigger_OutFlankenerkennung(){
	// //<FUNCTION_BODY>
// }

// //GENERATED
// void Rte_Write_OutJoystickTaster(int value){
	// localSenderReceiver[1] = value;
// }

// #define RTE_JOYSTICK_X_WRITE(value) localSenderReceiver[0] = value;
// #define RTE_JOYSTICK_Y_WRITE(value) localSenderReceiver[1] = value;
// #define RTE_JOYSTICK_TASTER_WRITE(value) localSenderReceiver[2] = value;



