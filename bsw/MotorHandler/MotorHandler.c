//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "MotorHandler.h"


//Globals
S8 motor_current_speed = 0;



//Functions
void motor_set_speed(S8 x, S8 y)
{
	S8 speed_left = x < 0 ? (y * (100 + x)) / 100 : y;
	S8 speed_right = x > 0 ? (y * (100 - x)) / 100 : y;
	
	ecrobot_set_motor_speed(MOTOR_LEFT, speed_left);
	ecrobot_set_motor_speed(MOTOR_RIGHT, speed_right);
	
	motor_current_speed = y;
}

S8 motor_read_speed()
{
	return motor_current_speed;
}
