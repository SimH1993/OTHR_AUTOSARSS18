#include "AdcIf.h"
#include "ecrobot.h"
#include "i2c_ext.h"

#define CONTROLBYTE (0x04)

const adc_read_fct_t AdcIfFctPtr={adc_int, adc_ext};

S16 adc_int(U8 port_id, U8 address){
	return ecrobot_get_RCX_sensor(port)>>2; //convert to 8 bit value
}
	
S16 adc_ext(U8 port_id, U8 address){
	U8 data[5];
	ecrobot_send_i2c(NXT_PORT_S4, address, CONTROLBYTE, data, 0);
	ecrobot_read_i2c(NXT_PORT_S4, address, CONTROLBYTE, data, 5); //analog value will be compared while reading previous value
	return ((S16)data[port_id + 1]);
}