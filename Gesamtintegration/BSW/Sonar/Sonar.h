#ifndef SONAR_H_
#define SONAR_H_

#define sonar_initialize_sensor(SENSOR_PORT) ecrobot_init_sonar_sensor(SENSOR_PORT)
#define sonar_read_distance(SENSOR_PORT) ecrobot_get_sonar_sensor(SENSOR_PORT) 
#define sonar_terminate_sensor(SENSOR_PORT) ecrobot_term_sonar_sensor(SENSOR_PORT)

#endif /* SONAR_H_ */
