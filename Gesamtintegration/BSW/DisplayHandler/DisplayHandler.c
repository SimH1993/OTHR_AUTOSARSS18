//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "DisplayHandler.h"


//Globals
int display_line_cnt = 0;


//Functions
void display_write_xy(int x, int y, const char *str)
{
	display_goto_xy(x, y);
	display_string(str);
	display_update();
	
	display_line_cnt = y;
}

void display_write_xy_num(int x, int y, int num)
{
	display_goto_xy(x, y);
	display_int(num,8);
	display_update();
	
	display_line_cnt = y;
}

void display_clear_line(int y)
{
	display_goto_xy(0, y);
	display_string(DISPLAY_EMPTY_LINE);
}

void display_write(const char *str)
{
	if(display_line_cnt >= DISPLAY_MAX_Y)
	{
		display_clear(0);
		display_goto_xy(0, 0);
		display_line_cnt = 0;
	}
	
	display_goto_xy(0, display_line_cnt);
	display_string(str);
	display_update();
	
	display_line_cnt++;
}

void display_write_int(int num)
{
	if(display_line_cnt >= DISPLAY_MAX_Y)
	{
		display_clear(0);
		display_goto_xy(0, 0);
		display_line_cnt = 0;
	}
	
	display_goto_xy(0, display_line_cnt);
	display_int(num, 8);
	display_update();
	
	display_line_cnt++;
}
//void display_clear(U32 updateToo) //already defined
