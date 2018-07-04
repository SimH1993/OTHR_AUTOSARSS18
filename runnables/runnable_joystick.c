#include "AdcIF.h"

//TODO: @CodeGen: Generate defines for hardware
//#define ADCPORT	NXT_PORT_A
//#define I2C_ADDRESS ADDRESS
//#define IC_PIN PIN

void runnable_joystick(){

	U8 data = ADC_Read_Value(1,ADCPORT,I2C_ADRESS,IC_PIN);	
	rte_write_runnable_joystick(data);
	
};
