#include "i2c.h"

U8 i2c_read(U8 port_id, U8 i2c_address){
	
	U8 buffer;
	ecrobot_read_i2c(port_id, i2c_address, buffer, &buffer, sizeof(buffer));
	return buffer;
}

void i2c_write(U8 port_id, U8 i2c_address, U8 data){
	
	ecrobot_send_i2c(port_id,i2c_address,data,&data,sizeof(data));
}

const i2c_read_fct_t I2CReadFctPtr[1];
const i2c_write_fct_t I2CWriteFctPtr[1];