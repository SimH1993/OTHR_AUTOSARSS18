#include <stdio.h>
#include "RTE_LED.h"

int main()
{
	RTE_INIT_DIO_INTERFACE();
    RTE_DIO_WRITE_DATA(LED,ALL_ON);
	return 0;
}



