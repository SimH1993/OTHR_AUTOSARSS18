typedef U8(*dio_read_fct_t)(U8 port_id, U8 i2c_address);
typedef void(*dio_write_fct_t)(U8 port_id, U8 i2c_address, U8 pin, U8 level);

extern const dio_read_fct_t DioIfReadFctPtr[];
extern const dio_write_fct_t DioIfWriteFctPtr[];

#define DIO_Read_Data(DIOIndex, Port, Adresse) \
	(*DioIfReadFctPtr[DIOIndex])(Port, Adresse)
	
#define DIO_Write_Data(DIOIndex, Port, Adresse, Pin, Level) \
	(*DioIfWriteFctPtr[DIOIndex])(Port, Adresse, Pin, Level)
