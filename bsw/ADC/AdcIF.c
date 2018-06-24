#include "AdcIf.h"
#include "ecrobot.h"
#include "i2c.h"

#define CONTROLBYTE (0x04)

const adc_read_fct_t AdcIfFctPtr={adc_int, adc_ext};

S16 adc_int(U8 port_id, U8 address){
	//return ecrobot_get_RCX_sensor(port)>>2; //convert to 8 bit value
	// Make the init call of the i2c
	return 0;
}
	
S16 adc_ext(U8 port_id, U8 address){
	U8 data[5];
	i2c_write_reg(NXT_PORT_S4, address, CONTROLBYTE, data, 0);
	i2c_read_reg(NXT_PORT_S4, address, CONTROLBYTE, data, 5); //analog value will be compared while reading previous value
	return ((S16)data[port_id + 1]);
}
