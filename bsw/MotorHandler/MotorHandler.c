//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "MotorHandler.h"


//Globals
S8 motor_current_speed = 0;



//Functions
void motor_set_speed(U32 port_left, U32 port_right, S8 speed_left, S8 speed_right)
{
	ecrobot_set_motor_speed(port_left, speed_left);
	ecrobot_set_motor_speed(port_right, speed_right);
	
	motor_current_speed = y;
}

S8 motor_read_speed()
{
	return motor_current_speed;
}
