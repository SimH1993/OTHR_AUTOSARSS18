typedef U8(*i2c_read_fct_t)(U8 port_id, U8 i2c_address);
typedef void(*i2c_write_fct_t)(U8 port_id, U8 i2c_address, U8 data);

extern const i2c_read_fct_t I2CReadFctPtr[1];
extern const i2c_write_fct_t I2CWriteFctPtr[1];

#define I2C_Read_Data(I2CIndex, Port, Adresse) \
	I2CReadFctPtr[I2CIndex](Port, Adresse)
	
#define I2C_Write_Data(I2CIndex, Port, Adresse, Data) \
	I2CWriteFctPtr[I2CIndex](Port, Adresse, Data)