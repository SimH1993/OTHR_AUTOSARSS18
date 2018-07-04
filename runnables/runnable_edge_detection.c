#include "AdcIF.h"

//TODO: @CodeGen: Generate defines for hardware
//#define PORT	NXT_PORT_A
//#define ADDRESS NXT_PORT_B
//#define IC_PIN NXT_PORT_C

U8 touched = 0;

void runnable_edge_detection(){

	//data is 1 if active 
	U8 data = adc_int(PORT, ADDRESS, IC_PIN);	
	
	if(!touched && data){
		
		touched = 1;
		rte_write_runnable_edge_detection(data);
	}
	else if(!data) {
		touched = 0;
	}
}