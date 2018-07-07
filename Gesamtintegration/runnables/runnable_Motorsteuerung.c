#include "../BSW/MotorHandler/MotorHandler.c"

void runnable_Motorsteuerung()
{	
	int data = RTE_READ_InMotorspeed();
	
	S8 motor_left = (S8)(data & 0x000000FF);
	S8 motor_right = (S8)((data & 0x0000FF00) >> 8);

	motor_set_speed(MOTOR_LEFT, MOTOR_RIGHT, motor_left, motor_right);	
}
