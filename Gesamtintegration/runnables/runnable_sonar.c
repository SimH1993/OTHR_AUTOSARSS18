#include "../BSW/Sonar/Sonar.h"

//TODO: @CodeGen: Generate defines for hardware
//#define SENSORPORT	NXT_PORT_S4

#define RTE_READ_RUNNABLE_SONAR(data) 1
#define RTE_WRITE_RUNNABLE_SONAR(data) 1

void runnable_sonar()
{
	S32 data = RTE_READ_RUNNABLE_SONAR();		
	RTE_WRITE_RUNNABLE_SONAR(data);
};
