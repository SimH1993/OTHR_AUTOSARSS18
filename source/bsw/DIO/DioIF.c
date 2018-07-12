#include "DioIF.h"
#include "../I2C/I2C.h"

U8 dio_read_ext(U8 port_id, U8 i2c_address){
	U8 dioStatus = 0;
	i2c_read(port_id, i2c_address, &dioStatus, 1);
	return dioStatus;
}

U8 pinState = 0xFF;

void dio_write_ext(U8 port_id, U8 i2c_address, U8 pin, U8 level){
	pin = pin & 0x07; // Can't select any pin higher than 7 (0-7)
	level = level & 0x01; // Level can only be 1 (high) or 0 (low)
	U8 newPinState = (pinState | (1 << pin)) & (~(level << pin));
	if ( newPinState != pinState) {
		pinState = newPinState;
		i2c_write(port_id, i2c_address, &pinState, 1);
	}
}

const dio_read_fct_t DioIfReadFctPtr[1] = {&dio_read_ext};
const dio_write_fct_t DioIfWriteFctPtr[1] = {&dio_write_ext};
