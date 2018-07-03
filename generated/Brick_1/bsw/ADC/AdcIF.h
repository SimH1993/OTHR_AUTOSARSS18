#include "ecrobot_interface.h"
#include "../I2C/i2c.h"

typedef U8(*adc_read_fct_t)(U8, U8, U8);
extern const adc_read_fct_t AdcIfFctPtr[];
#define ADC_Read_Value(ADCIndex, Port, I2C_Adress, ICpin) \
	(*AdcIfFctPtr[ADCIndex])(Port, I2C_Adress, ICpin)

U8 adc_int_init(U8);
