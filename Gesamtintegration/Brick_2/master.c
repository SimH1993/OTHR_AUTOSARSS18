#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "defines.h"

int localSenderReceiver[0];
int remotePorts[2];

DeclareCounter(CounterOne);
DeclareAlarm(alarmSWC3_Motorsteuerung);
DeclareEvent(TriggerMotorsteuerung);
DeclareEvent(TriggerBlinkersteuerung);
DeclareTask(SWC_3_Main);


void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
	
	if(portId == 0) SetEvent(SWC_3_Main, TriggerBlinkersteuerung);
}

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}

#include "../BSW/ComHandler/ComHandler.c"
#include "../BSW/I2C/I2C.h"
#include "../BSW/Sonar/Sonar.h"
#include "../BSW/DisplayHandler/DisplayHandler.c"


void ecrobot_device_initialize()
{

	com_init();
	#ifdef SONAR_SENSOR_PORT
	sonar_initialize_sensor(SONAR_SENSOR_PORT);
	#endif
	#ifdef I2C_PORT
	i2c_enable(I2C_PORT); //TODO: MIssing, needs merge
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




