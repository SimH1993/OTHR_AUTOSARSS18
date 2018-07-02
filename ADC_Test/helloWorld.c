#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "i2c.h"
#include "AdcIF.h"
#include "DioIF.h"

DeclareTask(Main); 
DeclareTask(Init); 

DeclareCounter(alarmCounter);

DeclareAlarm(WakeMain);

void myPrintln(const char *);

void user_1ms_isr_type2(void){ StatusType ercd;
	ercd = SignalCounter( alarmCounter );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	} 
} 

TASK(Init) {
	// ecrobot_set_RCX_power_source(NXT_PORT_S1);
	// ecrobot_set_RCX_power_source(NXT_PORT_S2);
	i2c_init(NXT_PORT_S4);
	TerminateTask(); /* Task beenden */	
}

U8 ledCounter = 0;
U8 ledState = 0;

TASK(Main) {
	// int res = ecrobot_get_RCX_sensor(NXT_PORT_S1);
	// int res2 = ecrobot_get_RCX_sensor(NXT_PORT_S4);
	// display_goto_xy(0,0);
	// display_unsigned(res, 5);
	// display_goto_xy(0,1);
	// display_unsigned(res2, 4);
	// display_update();
	
	display_goto_xy(0, 0);
	display_unsigned(ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0),5);
	display_goto_xy(0, 1);
	display_unsigned(ADC_Read_Value(1, NXT_PORT_S4, 0x48, 1),5);
	display_goto_xy(0, 2);
	display_unsigned(ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2),5);
	
	display_goto_xy(0, 3);
	display_unsigned(0xAA,5);
	display_update();
	
	
	//DIO_Write_Pin(0, NXT_PORT_S4, 0x20, ledCounter, ledState);
	//(*DioIfWriteFctPtr[0])(NXT_PORT_S4, 0x20, ledCounter, ledState);
	U8 pinStates =0xAA;
	i2c_write_reg(NXT_PORT_S4, 0x20, pinStates, pinStates, 1);
	ledCounter++;
	if ( ledCounter > 7) {
		ledCounter = 0;
		ledState = !ledState;
	}

	TerminateTask(); /* Task beenden */
}

void myPrintln(const char *s)
{
 static int y = 0;
 display_goto_xy(0,y);
 display_string(s);
 display_update();
 y++;
} 







