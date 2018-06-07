#ifndef RTE_LED_H_INCLUDED
#define RTE_LED_H_INCLUDED

#include <stdint.h>

#define EXTERN_DIO
#define INTERN_DIO

#define WRITE 1
#define READ 0

typedef enum {LED} DIO_Devices;
typedef enum {LEFT,RIGHT,ALL} DATA_TO_SEND;

void RTE_DIO_READ_DATA();
void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND option);

void Dio_Interface(uint8_t ReadOrWrite, DIO_Devices device, DATA_TO_SEND option);


#endif // RTE_LED_H_INCLUDED
