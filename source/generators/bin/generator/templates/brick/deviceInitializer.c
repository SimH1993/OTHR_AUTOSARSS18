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