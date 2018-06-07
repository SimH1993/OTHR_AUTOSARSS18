#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include "RTE_LED.h"

#define LED_EXTERN
#define LED_I2C_PORT NXT_PORT_S1
#define LED_I2C_ADRESS 0x20

/*TODO: DATENTYPEN AUF UINT UMSTELLEN
               DATENHALTUNG FÜR LED STATUS EINFÜGEN
                *I2C Enable <-> disable hinzufügen
                

 */
typedef enum {LED} DIO_Devices;
typedef enum {LEFT_ON,RIGHT_ON,ALL_ON, ALL_OFF} DATA_TO_SEND;

void RTE_INIT_DIO_INTERFACE();

void RTE_DIO_READ_DATA(DIO_Devices device);
void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND dataToSend);

typedef void(*WriteDataI2C)(DATA_TO_SEND dataToSend);
typedef void(*ReadDataI2C)();

void I2C_writeData(DATA_TO_SEND dataToSend);
void I2C_readData();

typedef struct i2c{
    
    WriteDataI2C writeData;
    ReadDataI2C readData;
        
} I2C;

typedef  void(*WriteData)(DIO_Devices device, DATA_TO_SEND dataToSend);
typedef  void (*ReadData)(DIO_Devices device);

void dio_interface_writeData(DIO_Devices device, DATA_TO_SEND dataToSend);
void dio_interface_readData(DIO_Devices device);

typedef struct dio_interface {

    I2C i2cHandler;
    int ledStatus[8]; 
    WriteData writeData;
    ReadData readData;

} DIO_INTERFACE;

DIO_INTERFACE Dio_Interface;


int main()
{
	RTE_INIT_DIO_INTERFACE();
    RTE_DIO_WRITE_DATA(LED,ALL_ON);
	return 0;
}



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
    
    u_int8_t data = 0;
    
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
    
    //ecrobot_send_i2c(LED_I2C_PORT,LED_I2C_ADRESS,data,&data,sizeof(data));

}

void I2C_readData(){
    
   
}
