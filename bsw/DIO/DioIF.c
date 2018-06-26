#include "DioIF.h"
#include "i2c.h"

U8 dio_int_init(U8 port_id){
	ecrobot_set_RCX_power_source(port_id);
	return 0;
}

U8 dio_read_int(U8 port_id, U8 i2c address){
	return ecrobot_get_touch_sensor(port_id);
}

U8 dio_read_ext(U8 port_id, U8 i2c address){
	U8 dioStatus = 0;
	i2c_read(port_id, i2c_address, &dioStatus, 1);
	return dioStatus;
}

void dio_write_int(U8 port_id, U8 i2c address, U8 data){
	
}

void dio_write_ext(U8 port_id, U8 i2c address, U8 data){
	i2c_write(port_id, i2c_address, &data, 1);
}

const dio_read_fct_t DioIfReadFctPtr[2] = {dio_read_int, dio_read_ext};
const dio_write_fct_t DioIfWriteFctPtr[2] = {dio_write_int, dio_write_ext};
