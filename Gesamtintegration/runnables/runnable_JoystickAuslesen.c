#include "../BSW/ADC/AdcIF.h"
#include "../BSW/SoundHandler/SoundHandler.h"

U8 joystickXRaw, joystickYRaw, joystickButtonRaw;
S8 joystickXPercent, joystickYPercent;
U8 joystickButton;

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
		counter = 0;
	}
	
	// Interpret raw values
	joystickXPercent = (S8) ((joystickXRaw / 255.0) * 200 - 100);
	joystickYPercent = (S8) ((joystickYRaw / 255.0) * 200 - 100);

	joystickButton = (joystickButtonRaw < 16);
	
	// Output the joystick values
	RTE_WRITE_OutJoystickHorizontal(joystickXRaw);
	RTE_WRITE_OutJoystickVertical(joystickYPercent);
	RTE_WRITE_OutJoystickTaster(joystickButton);
	
}
