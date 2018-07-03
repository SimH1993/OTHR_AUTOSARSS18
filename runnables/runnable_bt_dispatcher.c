#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "ComHandler.h"



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//TODO: This may need to be moved
//		bt_send will be called by anyone who wants to send data!

typedef struct
{
	U8 id;
	U8 flags;
	//U16 len;
} BT_NET_HEADER;


U8 bt_send(U8 id, U8 flags, int data)
{
	U8 buffer[sizeof(header) + sizeof(int)];
	BT_NET_HEADER *header = (BT_NET_HEADER*)buffer;
	
	header->id = id;
	header->flags = flags;
	*(int*)(buffer + sizeof(header)) = data;
	
	U32 sent = 0;
	while(sent < sizeof(buffer))
	{
		U32 len = com_send(buffer + sent, sizeof(buffer) - sent);
		if(!len)
			return 0;
		
		sent += len;
	}
	
	return 1;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////




void bt_runnable_dispatcher()
{
	//Only 1 single int data now (fixed length)
	U32 received = 0;
	BT_NET_HEADER header;
	
	while(received < sizeof(header))
	{
		U32 len = com_recv((U8*)header + received, sizeof(header) - received);
		if(!len)
			return;
		
		received += len;
	}
	
	received = 0;
	while(received < sizeof(int))
	{
		U32 len = com_recv(dataBuff + received, sizeof(int) - received);
		if(!len)
			return;
		
		received += len;
	}
	
	rte_set_data(header.id, *(int*)dataBuff);
}