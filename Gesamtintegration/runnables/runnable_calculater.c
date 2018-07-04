
//Globals
S8 speed_left = 0;
S8 speed_right = 0;


void runnable_calculate_speed()
{
	int data = rte_read_runnable_calculate_speed();
	
	S8 x = (S8)(data & 0x000000FF);
	S8 y = (S8)((data & 0x0000FF00) >> 8);
	
	S8 speed_left = x < 0 ? (y * (100 + x)) / 100 : y;
	S8 speed_right = x > 0 ? (y * (100 - x)) / 100 : y;

	int data = speed_right << 8 | speed_left;
	
	rte_write_runnable_calculate_speed(data);
}
