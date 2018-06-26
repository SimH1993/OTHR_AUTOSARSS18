//typedef U8(*i2c_read_fct_t)(U8 port_id, U8 i2c_address);
//typedef void(*i2c_write_fct_t)(U8 port_id, U8 i2c_address, U8 data);

//extern const i2c_read_fct_t I2CReadFctPtr[1];
//extern const i2c_write_fct_t I2CWriteFctPtr[1];

//#define I2C_Read_Data(I2CIndex, Port, Adresse) \
	I2CReadFctPtr[I2CIndex](Port, Adresse)
	
//#define I2C_Write_Data(I2CIndex, Port, Adresse, Data) \
	I2CWriteFctPtr[I2CIndex](Port, Adresse, Data)
//U8 i2c_read(U8 port_id, U8 i2c_address, U8 *buffer, U8 bufferSize);
//U8 i2c_write(U8 port_id, U8 i2c_ddress, U8 *buffer, U8 bufferSize);

/*
	i2c_read - Reads some data of an I2C connected device
		port_id [U8]: The NXT-Port the I2C shall be used
		i2c_address [U8]: Address of the I2C device
		buffer [U8*]: Pointer to the buffer the data will be written to
		bufferSize [U8]: Size of the buffer
*/
#define i2c_read(port_id, i2c_address, buffer, bufferSize) (i2c_read_reg(port_id, i2c_address, 0, buffer, bufferSize);)

/*
	i2c_read_reg - Reads some data from a specific register of an I2C connected device
		port_id [U8]: The NXT-Port the I2C shall be used
		i2c_address [U8]: Address of the I2C device
		regAddress [U8]: Register address of the requestes value
		buffer [U8*]: Pointer to the data buffer that will be written to
		bufferSize [U8]: Size of the data buffer
*/
#define i2c_read_reg(port_id, i2c_address, regAddress, buffer, bufferSize) (ecrobot_read_i2c(port_id, i2c_address, regAddress, buffer, bufferSize);)

/*
	i2c_write - Write some data to a specific register of an I2C connected device
		port_id [U8]: The NXT-Port the I2C shall be used
		i2c_address [U8]: Address of the I2C device
		buffer [U8*]: Pointer to the data buffer
		bufferSize [U8]: Size of the data buffer
*/
#define i2c_write(port_id, i2c_address, buffer, bufferSize) (i2c_write_reg(port_id, i2c_address, 0, buffer, bufferSize);)

/*
	i2c_write_reg - Write some data to a specific register of an I2C connected device
		port_id [U8]: The NXT-Port the I2C shall be used
		i2c_address [U8]: Address of the I2C device
		regAddress [U8]: Register address on the target to write the data to
		buffer [U8*]: Pointer to the data buffer
		bufferSize [U8]: Size of the data buffer
*/
#define i2c_write_reg(port_id, i2c_address, regAddress, buffer, bufferSize) (ecrobot_send_i2c(port_id, i2c_address, regAddress, buffer, bufferSize);)

/*
	i2c_init - Initialize the I2C Port
*/
#define i2c_init(port_id) (ecrobot_init_i2c(port_id, LOWSPEED))
