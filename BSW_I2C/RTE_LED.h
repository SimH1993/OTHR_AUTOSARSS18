#ifndef RTE_LED_H_INCLUDED
#define RTE_LED_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

#define LED_EXTERN
#define DIO_EXTERN

#ifdef LED_EXTERN

#define LED_I2C_PORT NXT_PORT_S1
#define LED_I2C_ADRESS 0x20
#define LED_NUMBER_OF_LEDS 4

#endif

/***************************************************************************************
 * 										Data															 
 ***************************************************************************************/

typedef enum {LED} DIO_Devices;
typedef enum {LEFT_ON,RIGHT_ON,ALL_ON, ALL_OFF} DATA_TO_SEND;

#ifdef LED_EXTERN

int LED_STATUS[LED_NUMBER_OF_LEDS];

#endif

/***************************************************************************************
 * 									RTE Functions															 
 ***************************************************************************************/

void RTE_INIT_DIO_INTERFACE();
void RTE_DINIT_DIO_INTERFACE();

void RTE_DIO_READ_DATA(DIO_Devices device);
void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND dataToSend);

/***************************************************************************************
 * 								I2C Hardware Abstraction																 
 ***************************************************************************************/

#ifdef DIO_EXTERN

typedef void(*WriteDataI2C)(DATA_TO_SEND dataToSend);
typedef void(*ReadDataI2C)();

void I2C_writeData(DATA_TO_SEND dataToSend);
void I2C_readData();

typedef struct i2c{
    
    WriteDataI2C writeData;
    ReadDataI2C readData;
        
} I2C;

#endif

/***************************************************************************************
 * 								DIO Hardware Abstraction																 
 ***************************************************************************************/
#ifdef DIO_EXTERN

typedef  void(*WriteDataToExternal)(DIO_Devices device, DATA_TO_SEND dataToSend);
typedef  void (*ReadDataExternal)(DIO_Devices device);

void dio_interface_writeDataToExternal(DIO_Devices device, DATA_TO_SEND dataToSend);
void dio_interface_readDataFromExternal(DIO_Devices device);

#endif

typedef struct dio_interface {

	#ifdef DIO_EXTERN
	
	WriteDataToExternal writeDataToExternal;
    ReadDataExternal readDataFromExternal;
	I2C i2cHandler;
	
		#ifdef LED_EXTERN
	
		int ledStatus[LED_NUMBER_OF_LEDS]; 

	 	#endif

	#endif

} DIO_INTERFACE;

DIO_INTERFACE Dio_Interface;

#endif // RTE_LED_H_INCLUDED
