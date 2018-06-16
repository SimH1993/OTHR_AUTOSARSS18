#define COM_CONNECT_PASSWD		"1337"
#define COM_RECEIVE_SPEED		33		//~30 times a second
#define COM_BUFF_SIZE			128
#define COM_MAX_PACKET_SIZE		32

static const U8 com_slave_addr[7] = {0x00, 0x16, 0x53, 0x17, 0x12, 0x8B, 0x00};

//Public globals
extern U8 com_initialized;

//Public functions
U8 com_init(U8 is_master);			//Returns 1 on success, 0 on failure
U32 com_send(U8 *buff, U32 len);	//Returns number of sent bytes, 0 on error [Async]
U32 com_recv(U8 *buff, U32 len);	//Returns number of received bytes, 0 on error [Async]
void com_terminate();
