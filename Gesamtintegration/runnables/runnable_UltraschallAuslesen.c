#include "../BSW/Sonar/Sonar.h"

//TODO: @CodeGen: Generate defines for hardware
//#define SENSORPORT	NXT_PORT_S4

void runnable_UltraschallAuslesen()
{
	S32 data = RTE_ADC_READ_Ultraschall();
	
	RTE_WRITE_OutUltraschall(data);
}
