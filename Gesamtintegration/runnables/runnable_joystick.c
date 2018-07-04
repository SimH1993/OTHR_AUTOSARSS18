#include "../BSW/ADC/AdcIF.h"

U8 joystickXRaw, joystickYRaw, joystickButtonRaw;
S8 joystickXPercent, joystickYPercent;
U8 joystickButton;

void runnable_joystick(){

	// Get raw adc values
	joystickXRaw = RTE_ADC_READ_JOYSTICKX();
	joystickYRaw = RTE_ADC_READ_JOYSTICKY();
	joystickButtonRaw = RTE_ADC_READ_JOYSTICKBUTTON();
	
	// Interpret raw values
	joystickXPercent = (S8) ((joystickXRaw / 255.0) * 200 - 100);
	joystickYPercent = (S8) ((joystickYRaw / 255.0) * 200 - 100);
	
	joystickButton = (joystickButtonRaw < 16);
	
	// Output the joystick values
	RTE_JOYSTICK_X_WRITE(joystickXPercent);
	RTE_JOYSTICK_Y_WRITE(joystickYPercent);
	RTE_JOYSTICK_TASTER_WRITE(joystickButton);
	
};
