#include "../BSW/Sonar/Sonar.h"

//TODO: @CodeGen: Generate defines for hardware
//#define SENSORPORT	NXT_PORT_S4

// #define RTE_ADC_READ_Ultraschall()	sonar_read_distance(SONAR_SENSOR_PORT)
// #define RTE_WRITE_OutUltraschall(value) localSenderReceiver[2] = value

void runnable_UltraschallAuslesen()
{
	ecrobot_sound_tone(1000, 10, 30);
	ecrobot_init_sonar_sensor(NXT_PORT_S2);
	// S32 data = RTE_ADC_READ_Ultraschall();
	S32 data = ecrobot_get_sonar_sensor(NXT_PORT_S2);
	
	//RTE_WRITE_OutUltraschall(data);
}
