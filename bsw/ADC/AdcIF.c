#include "AdcIf.h"
#include "ecrobot.h"
#include "i2c_ext.h"


const adc_read_fct_t AdcIfFctPtr={adc_int, adc_ext};

S16 adc_int(U8 port_id, U8 address){
	return ecrobot_get_RCX_sensor(port)>>2; //convert to 8 bit value
}


	
S16 adc_ext(U8 port_id, U8 address){
	U8 data = 0;
	i2c_write(address, (port_id&0x3), &data, 1);
	i2c_read(address, 2, &data, 1); //analog value will be compared while reading previous value
	i2c_read(address, 2, &data, 1);
	return data;
}
