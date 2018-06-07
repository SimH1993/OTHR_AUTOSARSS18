#include "RTE_LED.h"


void RTE_DIO_READ_DATA(){

    Dio_Interface(READ);

}

void RTE_DIO_WRITE_DATA(DIO_Devices device, DATA_TO_SEND option){

    Dio_Interface(WRITE, device, option);
}

void Dio_Interface(uint8_t ReadOrWrite, DIO_Devices device, DATA_TO_SEND option){

    if(ReadOrWrite){


        #ifdef EXTERN_DIO


        #endif // EXTERN_DIO


        #ifdef INTERN_DIO

        #endif // INTERN_DIO

    }else{

    }

}
