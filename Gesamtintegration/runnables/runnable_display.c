#include "../BSW/DisplayHandler/DisplayHandler.h"

#define RTE_READ_RUNNABLE_DISPLAY_WRITE()	0

typedef struct
{
	char *str;
} DISPLAY_DATA;

static const DISPLAY_DATA display_data[] = 
{
	{
		.str = "Vorwaerts!"
		
	},
	{
		.str = "Rueckwaerts!"
		
	}
};


void runnable_display_write()
{
	int id = RTE_READ_RUNNABLE_DISPLAY_WRITE();
	DISPLAY_DATA *cur_data = &display_data[id];
	
	display_clear(0);	
	display_write(cur_data->str);	
}



