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
	
	// display_goto_xy(0, 0);
	// U8 adc0 = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0);
	// display_unsigned(adc0,5);
	// // display_unsigned(ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0),5);
	// display_goto_xy(0, 1);
	// U8 adc1 = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 1);
	// display_unsigned(adc1,5);
	// // display_unsigned(ADC_Read_Value(1, NXT_PORT_S4, 0x48, 1),5);
	// display_goto_xy(0, 2);
	// U8 adc2 = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2);
	// display_unsigned(adc2,5);
	// display_unsigned(ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2),5);
	
	// display_goto_xy(0, 3);
	// display_unsigned(someOtherVarName,5);
	// display_goto_xy(0, 4);
	// display_unsigned(pinStates,5);
	// display_goto_xy(0, 5);
	//display_unsigned(anotherTryAtThis,5);
	display_update();
	
	
	// U8 adcJoystickX = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 0);
	// U8 adcJoystickY = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 1);
	// U8 adcJoystickButton = ADC_Read_Value(1, NXT_PORT_S4, 0x48, 2);
	
	// if (adcJoystickX > 240){
		// ledState = (ledState & ~0x03) | 0x01;
	// } else if (adcJoystickX < 16){
		// ledState = (ledState & ~0x03) | 0x02;
	// }
	
	// if (adcJoystickY > 240){
		// ledState = (ledState & ~0x0C) | 0x04;
	// } else if (adcJoystickY < 16){
		// ledState = (ledState & ~0x0C) | 0x08;
	// }
	
	// if (adcJoystickButton > 128) {
		// ledState = ~ledState;
	// }
	
	// i2c_write_reg(NXT_PORT_S4, 0x27, 0x00, &ledState, 1);
	
	//DIO_Write_Pin(0, NXT_PORT_S4, 0x20, ledCounter, ledState);
	//(*DioIfWriteFctPtr[0])(NXT_PORT_S4, 0x20, ledCounter, ledState);
	static U8 pinStates =0xAA;
	
	if ( pinStates > 10){
		ledCounter++;
		pinStates = 0;
	} else {
		pinStates++;
	}
	
	if ( ledCounter > 3) {
		ledCounter = 0;
		ledState = !ledState;
		// pinStates = ~pinStates;
		//i2c_write_reg(NXT_PORT_S4, 0x26, 0x00, &pinStates, 1);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 0, 0);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 1, 0);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 2, 1);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 3, 1);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 4, 1);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 5, 1);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 6, 1);
		// DIO_Write_Pin(0, NXT_PORT_S4, 0x26, 7, 1);
	}
	DIO_Write_Pin(0, NXT_PORT_S4, 0x26, ledCounter, ledState);
	
	// someOtherVarName = adc0;
	//someOtherVarName = anotherTryAtThis;
	
	// if ( someOtherVarName > 128 && pinStates != 0xAA){
		// // pinStates = 0xAA;
		// if ( debounce < 10){
			// if (pinStates!=0xAA){
				// pinStates = 0xAA;
				// i2c_write_reg(NXT_PORT_S4, 0x27, 0x00, &pinStates, 1);
			// }
		// } else {
			// debounce++;
		// }
	// }else if (someOtherVarName < 128 && pinStates == 0xAA) {
		// // pinStates = 0x00;
		// if ( debounce == 0){
			// if (pinStates==0xAA){
				// pinStates = 0x00;
				// i2c_write_reg(NXT_PORT_S4, 0x27, 0x00, &pinStates, 1);
			// }
		// } else {
			// debounce--;
		// }
	// }
	
	// i2c_write_reg(NXT_PORT_S4, 0x27, 0x00, &pinStates, 1);

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







