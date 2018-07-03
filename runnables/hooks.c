void ecrobot_device_initialize()
{
	//U8 com_init(U8 is_master);
	//U8 sonar_initialize_sensor(SENSOR_PORT);
	//i2c_enable(NXT_PORT_S1); //TODO: MIssing, needs merge
}

void ecrobot_device_terminate()
{	
	//void com_terminate();
	//U8 sonar_terminate_sensor(SENSOR_PORT);
	//i2c_disable(NXT_PORT_S1); //TODO: MIssing, needs merge
}

void user_1ms_isr_type2(void)
{
	StatusType ercd = SignalCounter(CounterOne);
	if(ercd != E_OK)
		ShutdownOS(ercd);
}