#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "defines.h"

int localSenderReceiver[4];
int remotePorts[2];
const U8 com_slave_addr[7] = COM_CONNECT_SLAVE_ADDRESS;

#ifdef COM_CONNECT_IS_MASTER
const U8 btIsmaster = 1;
#else
const U8 btIsmaster = 0;
#endif /* COM_CONNECT_IS_MASTER */

DeclareCounter(CounterOne);


DeclareAlarm(alarmSWC1_JoystickAuslesen);
DeclareAlarm(alarmSWC1_UltraschallAuslesen);
DeclareAlarm(alarmSWC1_FlankenErkennung);
DeclareAlarm(alarmSWC2_WerteBerechnen);
DeclareAlarm(alarmSWC4_DisplayAusgabe);
DeclareAlarm(alarmSWC4_SoundAusgabe);
DeclareEvent(TriggerJoystickAuslesen);
DeclareEvent(TriggerUltraschallAuslesen);
DeclareEvent(TriggerFlankenErkennung);
DeclareEvent(TriggerWerteBerechnen);
DeclareEvent(TriggerDisplayAusgabe);
DeclareEvent(TriggerSoundAusgabe);
DeclareTask(SWC_1_Main);
DeclareTask(SWC_2_Main);
DeclareTask(SWC_4_Main);



void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
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
	//com_init();
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

#include "SWC_1.c"
#include "SWC_2.c"
#include "SWC_4.c"




