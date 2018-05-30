/* i2cwritetest.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* I2C LEDs */

#define LED_Left_Up_ON       0xFB
#define LED_Left_Down_ON     0xF7
#define LED_Right_Up_ON      0xFE
#define LED_Right_Down_ON    0xFD

#define LEDs_FlashingLeft   (LED_Left_Up_ON | LED_Left_Down_ON)
#define LEDs_FlashingRight  (LED_Right_Up_ON | LED_Right_Down_ON)
#define LEDs_FlashingAll    (LEDs_FlashingLeft | LEDs_FlashingRight)

#define LEDs_All_OFF        0xEF

static U8 dataToSend = LEDs_All_OFF;
static U8 blinkAction = LEDs_All_OFF;
static U8 isON = 0;

/*
 * How to use it:
 *
 *  At startup call once:
 *
 *  i2c_enable(NXT_PORT_S1);  //if i2c is connected to Port 1
 *
 *  If you want to turn on/off a LED:
 *
 *  Set your Action to blinkAction. For example blinkAction = LEDs_FlashingLeft; --> flashing left
 *
 *
 *  static U8 dataToSend = LEDs_FlashingLeft;
 *  while (i2c_busy(NXT_PORT_S1) != 0);
 *  ecrobot_send_i2c(NXT_PORT_S1,0x20,dataToSend,&dataToSend,sizeof(dataToSend));
 *
 *  This example turns LED_Left_Up and LED_Left_Down on. If you want to turn off LEDs use the same Code
 *  with dataToSend = LEDs_All_OFF;
 *
 *
 *  Important!! Insert in your Code:
 *
 *  void ecrobot_device_terminate()
 *  {
 *	    i2c_disable(NXT_PORT_S1);   //if i2c is connected to Port 1
 *  }
 *
 */

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
DeclareTask(BlinkLEDs);

/* LEJOS OSEK hooks */
void ecrobot_device_terminate()
{
	i2c_disable(NXT_PORT_S1);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  StatusType ercd;

  ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
  if(ercd != E_OK)
  {
    ShutdownOS(ercd);
  }
}

/* Task1 executed only once at initialization */
TASK(Task1)
{
	i2c_enable(NXT_PORT_S1);
    
        blinkAction = LEDs_FlashingAll;

	TerminateTask();
}

/* Task2 executed every 1 sec */
TASK(BlinkLEDs)
{
    if(isON){
  
        dataToSend = LEDs_All_OFF;
        isON = 0;

	}else{
        
        dataToSend = blinkAction;
        isON = 1;
	}
    
    while (i2c_busy(NXT_PORT_S1) != 0);
    
    ecrobot_send_i2c(NXT_PORT_S1,0x20,dataToSend,&dataToSend,sizeof(dataToSend));

	TerminateTask();
}

