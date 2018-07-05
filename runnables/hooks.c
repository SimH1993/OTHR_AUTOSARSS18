//@codegen: Define setzen für I2C Port und Sonar
/*
	#define I2C_PORT_1
	#define I2C_PORT_2
	#define I2C_PORT_3
	#define I2C_PORT_4

	#define SONAR_SENSOR

	#define COM_MASTER

*/
void ecrobot_device_initialize()
{
	#ifdef COM_MASTER

	com_init(1);

	#else

	com_init(0);

	#endif 

	#ifdef SONAR_SENSOR

		sonar_initialize_sensor(SENSOR_PORT);

	#endif

	#ifdef I2C_PORT_1

		i2c_enable(NXT_PORT_S1);

	#endif

	#ifdef I2C_PORT_2

		i2c_enable(NXT_PORT_S2);

	#endif

	#ifdef I2C_PORT_3

		i2c_enable(NXT_PORT_S3);

	#endif

	#ifdef I2C_PORT_4

		i2c_enable(NXT_PORT_S4);

	#endif
}

void ecrobot_device_terminate()
{	
	com_terminate();
	
	#ifdef SONAR_SENSOR

		sonar_terminate_sensor(SENSOR_PORT);
	
	#endif

	#ifdef I2C_PORT_1

		i2c_disable(NXT_PORT_S1);

	#endif

	#ifdef I2C_PORT_2

		i2c_disable(NXT_PORT_S2);

	#endif

	#ifdef I2C_PORT_3

		i2c_disable(NXT_PORT_S3);

	#endif

	#ifdef I2C_PORT_4

		i2c_disable(NXT_PORT_S4);

	#endif
}

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}