#include "sonar.h"

//TODO: @CodeGen: Generate defines for hardware
//#define SENSORPORT	NXT_PORT_A



void runnable_sonar(){

	S32 data = sonar_read_distance(SENSORPORT);		
	rte_write_runnable_sonar(data);
};
