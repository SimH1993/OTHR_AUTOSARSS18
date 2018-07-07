#include "../BSW/DisplayHandler/DisplayHandler.c"

#define RTE_READ_RUNNABLE_DISPLAY_WRITE()	0

void runnable_DisplayAusgabe()
{
	int data = RTE_READ_InUltraschall();
	
	display_clear(0);	
	display_write_xy_num(0,0,data);
}



