typedef S16(*adc_read_fct_t)(U8 port_id, U8 address)
extern const adc_read_fct_t AdcIfFctPtr[2];
#define ADC_Read_Value(ADCIndex, Port, I2C_Adress, ICpin) \
	AdcIfFctPtr[ADCIndex] (Port, I2C_Adress,ICpin)