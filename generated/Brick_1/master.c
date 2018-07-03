#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

int localSenderReceiver[3];

DeclareCounter(CounterOne);

void user_1ms_isr_type2(void){ StatusType ercd;
	ercd = SignalCounter( CounterOne );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	} 
} 

#include "SWC_1.c"
// #include "SWC_2.c"
#include "SWC_4.c"




