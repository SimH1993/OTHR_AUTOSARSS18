//Predefined usage for 2 motors only
#define MOTOR_LEFT	NXT_PORT_A
#define MOTOR_RIGHT	NXT_PORT_B

#define motor_read_speed() motor_current_speed


//Public functions
void motor_set_speed(S8 x, S8 y);
