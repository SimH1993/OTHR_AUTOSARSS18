#include "DioIF.h"
#include "i2c.h"

U8 dio_read_ext(U8 port_id, U8 i2c_address){
	U8 dioStatus = 0;
	i2c_read(port_id, i2c_address, &dioStatus, 1);
	return dioStatus;
}

U8 pinState = 0xFF;

void dio_write_ext(U8 port_id, U8 i2c_address, U8 pin, U8 level){
	pinState = (pinState | (1 << pin)) & ((~level) << pin);
	i2c_write(port_id, i2c_address, &pinState, 1);
}

const dio_read_fct_t DioIfReadFctPtr[1] = {&dio_read_ext};
const dio_write_fct_t DioIfWriteFctPtr[1] = {&dio_write_ext};
