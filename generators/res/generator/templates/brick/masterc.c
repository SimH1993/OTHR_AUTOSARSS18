#include "defines.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

int localSenderReceiver[<LOCAL_SENDER_RECEIVER_SIZE>];
int remotePorts[<REMOTE_SENDER_RECEIVER_SIZE>];
const U8 com_slave_addr[7] = COM_CONNECT_SLAVE_ADDRESS;

#ifdef COM_CONNECT_IS_MASTER
const U8 btIsmaster = 1;
#else
const U8 btIsmaster = 0;
#endif /* COM_CONNECT_IS_MASTER */

DeclareCounter(CounterOne);
<DECLARES>

void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
	
	<REMOTE_TRIGGERS>
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
	<I2C_INIT>
	<ADC_INIT>
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

<INCLUDES>

<FUNCTIONS>