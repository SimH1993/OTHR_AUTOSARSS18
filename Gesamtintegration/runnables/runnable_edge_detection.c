#include "../BSW/ADC/AdcIF.h"

#define RTE_READ_EDGE_DETECTION() 1
#define RTE_WRITE_RUNNABLE_EDGE_DETECTION(data) 1


U8 touched = 0;

void runnable_edge_detection(){

	//data is 1 if active 
	U8 data = RTE_READ_EDGE_DETECTION();	
	
	if(!touched && data){
		
		touched = 1;
		RTE_WRITE_RUNNABLE_EDGE_DETECTION(data);
	}
	else if(!data) {
		touched = 0;
	}
}
