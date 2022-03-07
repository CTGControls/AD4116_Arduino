#include "AD4116_write.h"
#include <SPI.h>


uint8_t AD4116_write(uint8_t ChipSelectPin, byte comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(50);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(150);

    SPI.transfer(comms);
    unsigned int results = SPI.transfer(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}