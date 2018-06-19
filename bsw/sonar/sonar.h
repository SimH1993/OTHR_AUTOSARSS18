//used port for sonar sensor
#define SONAR_SENSOR_PORT	NXT_PORT_S1

//public functions
void sonar_initialize_sensor();
S32 sonar_read_distance();
void sonar_terminate_sensor();
