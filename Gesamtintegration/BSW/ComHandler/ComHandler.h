#ifndef COMHANDLER_H_
#define COMHANDLER_H_

#define COM_CONNECT_PASSWD		"1337"	//connection password/session protector
#define COM_CONNECT_TIMEOUT		5000	//time in ms until connection fails on connect
#define COM_RECEIVE_SPEED		33		//~30 times a second
#define COM_BUFF_SIZE			128		//max buffer size to store packets

//static const U8 com_slave_addr[7] = COM_CONNECT_SLAVE_ADDRESS;
extern const U8 com_slave_addr[];

//Public globals
extern U8 com_initialized;

typedef struct
{
	U8 id;
	U8 flags;
	//U16 len;
} BT_NET_HEADER;

//Public functions
U8 com_init();						//Returns 1 on success, 0 on failure
U32 com_send(U8 *buff, U32 len);				//Returns number of sent bytes, 0 on error [Async]
U8 com_send_packet(U8 id, U8 flags, int data);	//Returns 1 on success, 0 on failure [Async]
U32 com_recv(U8 *buff, U32 len);				//Returns number of received bytes, 0 on error [Async]
void com_terminate();

// Is defined in the master.c
void rte_set_data(int portId, int data);

#endif /* COMHANDLER_H_ */
