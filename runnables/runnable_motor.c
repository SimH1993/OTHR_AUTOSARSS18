#include "MotorHandler.h"


S8 motor_left, motor_right;

void runnable_motor() {	

	int data = rte_read_runnable_motor();
	
	S8 motor_left = (S8)(data & 0x000000FF);
	S8 motor_right = (S8)((data & 0x0000FF00) >> 8);


	motor_set_speed(motor_left, motor_right);	
	
}