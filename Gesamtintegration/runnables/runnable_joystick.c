#include "../bsw/AdcIF.h"

U8 joystickdata[5];

void Joystick_auslesen(){

	joystickdata = ADC_Read_Value(1,<ADCPORT>,<I2C_ADRESS>,<ICPIN>);
};
