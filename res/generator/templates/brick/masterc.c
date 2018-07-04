#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

int localSenderReceiver[<LOCAL_SENDER_RECEIVER_SIZE>];
int remotePorts[<REMOTE_SENDER_RECEIVER_SIZE>];

<DECLARES>

void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
	
	<REMOTE_TRIGGERS>
}

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

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}

<INCLUDES>

<FUNCTIONS>