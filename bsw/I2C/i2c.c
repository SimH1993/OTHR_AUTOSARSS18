#include "i2c.h"

U8 i2c_read(U8 port_id, U8 i2c_address, U8 *buffer, U8 bufferSize){
	ecrobot_read_i2c(port_id, i2c_address, 0, buffer, bufferSize);
	return 0; // Exchange with RTE_OK value
}

U8 i2c_read_reg(U8 port_id, U8 i2c_address, U8 regAddress, U8 *buffer, U8 bufferSize){
	ecrobot_read_i2c(port_id, i2c_address, regAddress, buffer, bufferSize);
	return 0; // Exchange with RTE_OK value
}

U8 i2c_write(U8 port_id, U8 i2c_address, U8 *buffer, U8 bufferSize){
	ecrobot_send_i2c(port_id,i2c_address, 0, buffer, bufferSize);
	return 0; // Exchange with RTE_OK value
}

U8 i2c_write_reg(U8 port_id, U8 i2c_address, U8 regAddress, U8 *buffer, U8 bufferSize){
	ecrobot_send_i2c(port_id,i2c_address, regAddress, buffer, bufferSize);
	return 0; // Exchange with RTE_OK value
}

//const i2c_read_fct_t I2CReadFctPtr[1];
//const i2c_write_fct_t I2CWriteFctPtr[1];
