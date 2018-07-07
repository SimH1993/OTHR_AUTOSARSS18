#include "../BSW/DisplayHandler/DisplayHandler.h"

void runnable_DisplayAusgabe()
{
	int data = RTE_READ_InUltraschall();
	
	display_clear(0);	
	display_write_xy_num(0,0,data);
}



