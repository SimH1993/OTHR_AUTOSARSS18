#include "RTE_LED.h"


void RTE_INIT_DIO_INTERFACE(){

    int i;
    
	Dio_Interface.writeData = dio_interface_writeData;
    Dio_Interface.readData = dio_interface_readData;
    Dio_Interface.i2cHandler.readData = I2C_readData;
    Dio_Interface.i2cHandler.writeData = I2C_writeData;
    
    for(i = 0; i < 8; i++){
        
            Dio_Interface.ledStatus[i] = 0;
        }
}


void RTE_DIO_READ_DATA(DIO_Devices device){

    Dio_Interface.readData(device);

}

void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND dataToSend){

    Dio_Interface.writeData(device, dataToSend);
}


void dio_interface_writeData(DIO_Devices device, DATA_TO_SEND dataToSend){


    switch (device) {
        
    case LED:
    
        #ifdef LED_EXTERN
    
        Dio_Interface.i2cHandler.writeData(dataToSend);
        
        #else
        
        #endif
        
        break;
    
    default:
    
        break;
        
    };

}

void dio_interface_readData(){
    
    
}


void I2C_writeData(DATA_TO_SEND dataToSend){
    
    U8 data = 0;
    
    switch (dataToSend){
       
        case ALL_ON:
        
            data = 0xF0;
            break;
            
        case ALL_OFF:
        
            data = 0xEF;
            break;
            
        case LEFT_ON:
            
            data = 0xF3;
            break;
            
        case RIGHT_ON:
        
            data = 0xFC;
            break;
        
    };
    
    ecrobot_send_i2c(LED_I2C_PORT,LED_I2C_ADRESS,data,&data,sizeof(data));

}

void I2C_readData(){
    
   
}
