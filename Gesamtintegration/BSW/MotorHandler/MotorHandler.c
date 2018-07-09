//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "MotorHandler.h"


//Functions
void motor_set_speed(U32 port, S8 value)
{
	ecrobot_set_motor_speed(port, value);
}

