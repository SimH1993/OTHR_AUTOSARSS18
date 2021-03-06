#include "MotorHandler.h"

//TODO: @CodeGen: Generate defines for hardware
//#define MOTOR_PORT_LEFT	NXT_PORT_A
//#define MOTOR_PORT_RIGHT	NXT_PORT_B

void runnable_motor() {	

	int data = rte_read_runnable_motor();
	
	S8 motor_left = (S8)(data & 0x000000FF);
	S8 motor_right = (S8)((data & 0x0000FF00) >> 8);


	motor_set_speed(MOTOR_PORT_LEFT, MOTOR_PORT_RIGHT, motor_left, motor_right);	
	
}