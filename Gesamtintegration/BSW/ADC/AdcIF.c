#include "AdcIf.h"
#include "../I2C/I2C.h"

#define CONTROLBYTE (0x04)

U8 adc_int_init(U8 port_id){
	ecrobot_set_RCX_power_source(port_id);
	return 0;
}

U8 adc_int(U8 port_id, U8 address, U8 icPin){
	return ecrobot_get_RCX_sensor(port_id)>>2; //convert to 8 bit value
}
	
U8 adc_ext(U8 port_id, U8 address, U8 icPin){
	U8 data[5];
	if ( icPin > 4){
		return 0x00;
	}
	i2c_write_reg(port_id, address, CONTROLBYTE, data, 0);
	i2c_read_reg(port_id, address, CONTROLBYTE, data, 5);
	i2c_write_reg(port_id, address, CONTROLBYTE, data, 0);
	i2c_read_reg(port_id, address, CONTROLBYTE, data, 5); //analog value will be compared while reading previous value
	return data[icPin + 1];
}

const adc_read_fct_t AdcIfFctPtr[2]={&adc_ext, &adc_int};
