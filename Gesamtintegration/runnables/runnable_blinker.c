#include "../BSW/I2C/I2C.h"

#define PORT	NXT_PORT_S1 //TODO: generate this dynamically

#define RTE_READ_RUNNABLE_BLINKER_FLASH_ALL() 0

U8 blinkState = 0;


void runnable_blinker_flash_all()
{
	int is_activated = RTE_READ_RUNNABLE_BLINKER_FLASH_ALL();
	if(is_activated)
	{
		U8 dataToSend = blinkState ? LEDs_All_OFF : LEDs_FlashingAll;
		
		//TODO: Change to macro call
		while (i2c_busy(PORT) != 0)
			;
		i2c_write_reg(PORT, 0x20, dataToSend, &dataToSend, sizeof(dataToSend));
		
		blinkState = !blinkState;
	}
	else if(blinkState)
	{
		U8 dataToSend = LEDs_All_OFF;
		
		//TODO: Change to macro call
		while (i2c_busy(PORT) != 0)
			;
		i2c_write_reg(PORT, 0x20, dataToSend, &dataToSend, sizeof(dataToSend));
		
		blinkState = 0;
	}
}