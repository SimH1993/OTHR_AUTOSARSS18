#include "../bsw/AdcIF.h"

U8 touched = 0;
U8 port = 0;

void Flankenerkennung(U8 TASTER_PORT){

	//port ist 1 oder 0 für aktiv oder nichtaktiv
	port = RTE_ADC(<TOUCHPORT>);
	
	if(!touched && port){
		
		touched = 1;
		SetEvent(SWC3,TASTERPORT);
	}
	
	if(port == 0){
		
		touched = 0;
	}
	
};
