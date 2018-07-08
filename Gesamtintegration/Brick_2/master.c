#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "defines.h"

int localSenderReceiver[0];
int remotePorts[2];
const U8 com_slave_addr[7] = COM_CONNECT_SLAVE_ADDRESS;

#ifdef COM_CONNECT_IS_MASTER
const U8 btIsmaster = 1;
#else
const U8 btIsmaster = 0;
#endif / *COM_CONNECT_IS_MASTER */

DeclareCounter(CounterOne);
DeclareAlarm(alarmSWC3_Motorsteuerung);
DeclareEvent(TriggerMotorsteuerung);
DeclareEvent(TriggerBlinkersteuerung);
DeclareTask(SWC_3_Main);


void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
	display_goto_xy(0,0);
	display_int(remotePorts[0], 6);
	display_goto_xy(0,1);
	display_int(remotePorts[1], 6);
	display_update();
	
	if(portId == 0) SetEvent(SWC_3_Main, TriggerBlinkersteuerung);
}

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}

#include "../BSW/ADC/AdcIF.h"
#include "../BSW/ComHandler/ComHandler.h"
#include "../BSW/DIO/DioIF.h"
#include "../BSW/DisplayHandler/DisplayHandler.h"
#include "../BSW/I2C/I2C.h"
#include "../BSW/MotorHandler/MotorHandler.h"
#include "../BSW/Sonar/Sonar.h"
#include "../BSW/SoundHandler/SoundHandler.h"
#include "../BSW/Utility/Utility.h"


void ecrobot_device_initialize()
{

	com_init();
	#ifdef SONAR_SENSOR_PORT
	sonar_initialize_sensor(SONAR_SENSOR_PORT);
	#endif
	#ifdef I2C_PORT
	i2c_init(I2C_PORT); //TODO: MIssing, needs merge
	#endif
}

void ecrobot_device_terminate()
{	
	com_terminate();
	#ifdef SONAR_SENSOR_PORT
	sonar_terminate_sensor(SONAR_SENSOR_PORT);
	#endif
	#ifdef I2C_PORT
	i2c_disable(I2C_PORT); //TODO: MIssing, needs merge
	#endif
}

#include "SWC_3.c"




