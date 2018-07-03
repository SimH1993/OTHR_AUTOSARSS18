#include "../bsw/i2c_led.h"

#define PORT	NXT_PORT_S1 //TODO: generate this dynamically

U8 blinkState = 0;


void runnable_blinker_flash_all()
{
	int is_activated = rte_read_runnable_blinker_flash_all();
	if(is_activated)
	{
		U8 dataToSend = blinkState ? LEDs_All_OFF : LEDs_FlashingAll;
		
		while (i2c_busy(PORT) != 0)
			;
		
		ecrobot_send_i2c(PORT, 0x20,dataToSend, &dataToSend, sizeof(dataToSend));
		
		blinkState = !blinkState;
	}
	else if(blinkState)
	{
		U8 dataToSend = LEDs_All_OFF;
		
		while (i2c_busy(PORT) != 0)
			;
		
		ecrobot_send_i2c(PORT, 0x20,dataToSend, &dataToSend, sizeof(dataToSend));
		
		blinkState = 0;
	}
}