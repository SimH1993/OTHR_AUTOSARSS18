#include "AdcIF.h"

U8 touched = 0;

void runnable_edge_detection(){

	//data is 1 if active 
	U8 data = rte_read_edge_detection();	
	
	if(!touched && data){
		
		touched = 1;
		rte_write_runnable_edge_detection(data);
	}
	else if(!data) {
		touched = 0;
	}
}