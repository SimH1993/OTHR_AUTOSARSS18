#include "../BSW/ADC/AdcIF.c"

U8 joystickXRaw, joystickYRaw, joystickButtonRaw;
S8 joystickXPercent, joystickYPercent;
U8 joystickButton;

void runnable_JoystickAuslesen(){

	// Get raw adc values
	joystickXRaw = RTE_ADC_READ_JostickHorizontal();
	joystickYRaw = RTE_ADC_READ_JoystickVertical();
	joystickButtonRaw = RTE_ADC_READ_Taster();
	
	// Interpret raw values
	joystickXPercent = (S8) ((joystickXRaw / 255.0) * 200 - 100);
	joystickYPercent = (S8) ((joystickYRaw / 255.0) * 200 - 100);
	
	joystickButton = (joystickButtonRaw < 16);
	
	// Output the joystick values
	RTE_WRITE_OutJoystickHorizontal(joystickXRaw);
	RTE_WRITE_OutJoystickVertical(joystickYPercent);
	RTE_WRITE_OutJoystickTaster(joystickButton);
}
