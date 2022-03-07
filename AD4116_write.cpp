#include "AD4116_write.h"



// uint8_t AD4116_write(uint8_t ChipSelectPin, uint8_t comms)
// {

//     pinMode(ChipSelectPin,OUTPUT);
    
//     delay(50);
    
//     SPI.setBitOrder(MSBFIRST);
//     SPI.setDataMode(SPI_MODE3);
    
//     digitalWrite(ChipSelectPin,LOW); //enable device

//     delay(150);

//     SPI.transfer(comms);
//     unsigned int results = SPI.transfer(0x00);
    
//     digitalWrite(ChipSelectPin,HIGH); //disable device

//     return results;
// }

uint8_t AD4116_write(SPIClass& spi, uint8_t ChipSelectPin, uint8_t comms, byte data[])
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(50);
    
    spi.setBitOrder(MSBFIRST);
    spi.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(150);

    spi.transfer(comms);
    for (int i = 0 ; i < sizeof(data)/sizeof(data[0]); i++){
        spi.transfer(data[i]);
    }
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return 0;
}