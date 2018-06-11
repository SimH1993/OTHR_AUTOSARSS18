#define DISPLAY_MAX_X		15
#define DISPLAY_MAX_Y		17
#define DISPLAY_EMPTY_LINE	"               "

//Public functions
void display_write_xy(int x, int y, const char *str);
void display_clear_line(int y);
void display_write(const char *str);
//void display_clear(U32 updateToo) //already defined