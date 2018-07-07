#include "../BSW/ADC/AdcIF.h"
#include "../BSW/SoundHandler/SoundHandler.h"

U8 joystickXRaw, joystickYRaw, joystickButtonRaw;
S8 joystickXPercent, joystickYPercent;
int joystickButton;

// #define RTE_ADC_READ_JostickHorizontal()	ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0)
// #define RTE_ADC_READ_Taster()			ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2)

U8 counter = 0;

void runnable_JoystickAuslesen(){

	// Get raw adc values
	if ( counter == 0){
		joystickXRaw = RTE_ADC_READ_JostickHorizontal();
		counter++;
	} else if ( counter == 1) {
		joystickYRaw = RTE_ADC_READ_JoystickVertical();
		counter++;
	} else {
		joystickButtonRaw = RTE_ADC_READ_Taster();
		//joystickButtonRaw = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0);
		counter = 0;
	}
	
	// Interpret raw values
	joystickXPercent = (S8) ((joystickXRaw / 255.0) * 200 - 100);
	joystickYPercent = (S8) ((joystickYRaw / 255.0) * 200 - 100);
	
	joystickButton = (int) (joystickButtonRaw < 16);
	
	// Output the joystick values
	// RTE_WRITE_OutJoystickHorizontal(joystickXRaw);
	// RTE_WRITE_OutJoystickVertical(joystickYPercent);
	RTE_WRITE_OutJoystickTaster(joystickButton);
	
}
