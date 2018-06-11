#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "sonar.h"

int sonar_sensor_initialized = 0;


//initializes the communication used for the sonar sensor.
void sonar_initialize_sensor() 
{
	if(!sonar_sensor_initialized)
	{
		ecrobot_init_sonar_sensor(SONAR_SENSOR_PORT);
		sonar_sensor_initialised = 1;
	}
}


//returns the distance the sonar sensor reads in cm
S32 sonar_read_distance() 
{	
	//Initialize sonar sensor if it is not initialized yet
	sonar_initialize_sensor();
	
	return ecrobot_get_sonar_sensor(SONAR_SENSOR_PORT);
	
}

//terminates the communication used for the sonar sensor.
void sonar_terminate_sensor() 
{
	ecrobot_term_sonar_sensor(SONAR_SENSOR_PORT);
}