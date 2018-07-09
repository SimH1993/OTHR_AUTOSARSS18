#include "../BSW/DIO/DioIf.c"

void runnable_Blinkersteuerung()
{
	static U8 ledCounter = 0;
	static U8 dir = 1;
	
	switch (ledCounter) {
		case 3:
		RTE_DIO_WRITE_BlinkerLED4(dir);
		case 2:
		RTE_DIO_WRITE_BlinkerLED3(dir);
		case 1:
		RTE_DIO_WRITE_BlinkerLED2(dir);
		case 0:
		RTE_DIO_WRITE_BlinkerLED1(dir);
		break;
	}
	
	ledCounter++;
	
	if ( ledCounter > 3 ) {
		dir = !dir;
		ledCounter = 0;
	}
	
}
