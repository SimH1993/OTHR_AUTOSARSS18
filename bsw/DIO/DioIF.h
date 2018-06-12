typedef U8(*dio_read_fct_t)(U8 port_id, U8 i2c_address);
typedef void(*dio_write_fct_t)(U8 port_id, U8 i2c_address, U8 data);

extern const dio_read_fct_t DioIfReadFctPtr[2];
extern const dio_write_fct_t DioIfWriteFctPtr[2];

#define DIO_Read_Data(DIOIndex, Port, Adresse) \
	DioIfReadFctPtr[DIOIndex](Port, Adresse)
	
#define DIO_Write_Data(DIOIndex, Port, Adresse, Data) \
	DioIfWriteFctPtr[DIOIndex](Port, Adresse, Data)