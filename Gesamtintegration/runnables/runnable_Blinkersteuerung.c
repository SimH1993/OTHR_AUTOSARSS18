#include "../BSW/DIO/DioIf.c"

void runnable_Blinkersteuerung()
{
	static U8 blinkState=0;
	blinkState^=1;
	DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 0, blinkState);
	ecrobot_sound_tone(1000, 100, 50);
}
