#include "../BSW/MotorHandler/MotorHandler.c"

void runnable_Motorsteuerung()
{	
	int data = RTE_READ_InMotorspeed();
	
	S8 motor_left = (S8)(data & 0x000000FF);
	S8 motor_right = (S8)((data & 0x0000FF00) >> 8);

	RTE_ECR_MOTOR_WRITE_MotorLinks(motor_left);
	RTE_ECR_MOTOR_WRITE_MotorRechts(motor_right);
}
