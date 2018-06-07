#ifndef RTE_LED_H_INCLUDED
#define RTE_LED_H_INCLUDED

#include <stdint.h>

#define LED_EXTERN
#define LED_I2C_PORT NXT_PORT_S1
#define LED_I2C_ADRESS 0x20


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

#endif // RTE_LED_H_INCLUDED
