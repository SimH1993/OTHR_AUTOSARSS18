#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"



void user_1ms_isr_type2(void){}

DeclareTask(Main);


int y = 0;


void myPrint(const char *s)
{
   display_goto_xy(0,y);
   display_string(s);
   display_update();
}

TASK(Main)
{
    U8 data[7];
	
	if (!ecrobot_get_bt_device_address(data))
	{
	   myPrint("failure");
	}
	else
	{
	   for(int f=0;f<7;f++)
	   {
	      display_goto_xy(0,y);
		  display_int(data[f],0);
		  display_update();
		  y++;
	   }
	}
	TerminateTask();
}

