#include "ecrobot_interface.h"

typedef U8(*dio_read_fct_t)(U8, U8);
typedef void(*dio_write_fct_t)(U8, U8, U8, U8);

extern const dio_read_fct_t DioIfReadFctPtr[];
extern const dio_write_fct_t DioIfWriteFctPtr[];

#define DIO_Read_Pin(DIOIndex, Port, Adresse) \
	(*DioIfReadFctPtr[DIOIndex])(Port, Adresse)
	
#define DIO_Write_Pin(DIOIndex, Port, Adresse, Pin, Level) \
	(*DioIfWriteFctPtr[DIOIndex])(Port, Adresse, Pin, Level)
