#include "../BSW/ADC/AdcIF.h"

void runnable_FlankenErkennung()
{
	static U8 touched=0;
	//data is 1 if active 
	U8 data = (RTE_ADC_READ_BlinkerTaster() < 128);
	
	if(!touched && data)
	{
		touched = 1;
		RTE_TRIGGER_OutFlankenerkennung();
	}
	else if(!data)
	{
		touched = 0;
	} 
}
