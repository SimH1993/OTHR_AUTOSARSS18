#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

int localSenderReceiver[<LOCAL_SENDER_RECEIVER_SIZE>];
int remotePorts[<REMOTE_SENDER_RECEIVER_SIZE>];

void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
	
	<REMOTE_TRIGGERS>
}

<DECLARES>

<INCLUDES>

<FUNCTIONS>