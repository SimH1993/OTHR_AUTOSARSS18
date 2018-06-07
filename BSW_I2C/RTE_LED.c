#include "RTE_LED.h"

/***************************************************************************************
 * 																				RTE Functions															 
 ***************************************************************************************/

void RTE_INIT_DIO_INTERFACE(){
	
    #ifdef DIO_EXTERN

    int i;
	
	Dio_Interface.writeDataToExternal = dio_interface_writeDataToExternal;
    Dio_Interface.readDataFromExternal = dio_interface_readDataFromExternal;
	
    Dio_Interface.i2cHandler.readData = I2C_readData;
    Dio_Interface.i2cHandler.writeData = I2C_writeData;
	
		#ifdef LED_EXTERN
	
		for(i = 0; i < LED_NUMBER_OF_LEDS; i++){
			
				Dio_Interface.ledStatus[i] = 0;
				LED_STATUS[i] = 0;
			}
		
		#endif
		
	//i2c_enable(LED_I2C_PORT);
		
	#endif
}

void RTE_DINIT_DIO_INTERFACE(){
	
    #ifdef DIO_EXTERN

	//i2c_disable(LED_I2C_PORT);
	
    #endif
}


void RTE_DIO_READ_DATA(DIO_Devices device){

    #ifdef DIO_EXTERN

    Dio_Interface.readDataFromExternal(device);

    #endif

}

void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND dataToSend){

    #ifdef DIO_EXTERN

    Dio_Interface.writeDataToExternal(device, dataToSend);

    #endif
}

/***************************************************************************************
 * 																DIO Hardware Abstraction																 
 ***************************************************************************************/

#ifdef DIO_EXTERN

void dio_interface_writeDataToExternal(DIO_Devices device, DATA_TO_SEND dataToSend){


    switch (device) {
        
    case LED:
    
        Dio_Interface.i2cHandler.writeData(dataToSend);
        
        break;
    
    default:
    
        break;
        
    };

}

void dio_interface_readDataFromExternal(DIO_Devices device){

	#ifdef LED_EXTERN

	int i;
	
	for(i=0; i <LED_NUMBER_OF_LEDS; i++){
		
		LED_STATUS[i] =  Dio_Interface.ledStatus[i];
	}
	
	#endif
}

/***************************************************************************************
 * 																I2C Hardware Abstraction																 
 ***************************************************************************************/

void I2C_writeData(DATA_TO_SEND dataToSend){

    #ifdef LED_EXTERN
    
    uint8_t data = 0;
	int i;
    
    switch (dataToSend){
       
        case ALL_ON:
        
            data = 0xF0;
			
			for(i=0; i < LED_NUMBER_OF_LEDS; i++){

				Dio_Interface.ledStatus[i] = 1;
			}
			
            break;
            
        case ALL_OFF:
        
            data = 0xFF;
			
			for(i=0; i < LED_NUMBER_OF_LEDS; i++){

				Dio_Interface.ledStatus[i] = 0;
			}
            break;
            
        case LEFT_ON:
            
            data = 0xF3;
			
			for(i=0; i < LED_NUMBER_OF_LEDS; i++){

				Dio_Interface.ledStatus[i] = 0;
			}
			
			Dio_Interface.ledStatus[2] = 1;
			Dio_Interface.ledStatus[3] = 1;
			
            break;
            
        case RIGHT_ON:
        
			for(i=0; i < LED_NUMBER_OF_LEDS; i++){

				Dio_Interface.ledStatus[i] = 0;
			}
			
			Dio_Interface.ledStatus[0] = 1;
			Dio_Interface.ledStatus[1] = 1;
		
            data = 0xFC;
            break;
        
    };
    
 //   ecrobot_send_i2c(LED_I2C_PORT,LED_I2C_ADRESS,data,&data,sizeof(data));

 #endif


}

void I2C_readData(){
    
    #ifdef LED_EXTERN

    #endif
   
}

#endif
