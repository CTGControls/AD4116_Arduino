#include "AD4116_read.h"
#include <SPI.h>

uint8_t AD4116_read(uint8_t ChipSelectPin, uint8_t comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(50);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(150);

    SPI.transfer(comms);
    uint8_t results = SPI.transfer(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}


uint16_t AD4116_read16(uint8_t ChipSelectPin, uint8_t comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(50);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(150);

    SPI.transfer(comms);
    uint16_t results = SPI.transfer16(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}

uint32_t AD4116_read24(uint8_t ChipSelectPin, uint8_t comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(50);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(150);

    SPI.transfer(comms);
    uint32_t resultsW1 = SPI.transfer(0x00);
    uint32_t resultsW2 = SPI.transfer(0x00);
    uint32_t resultsW3 = SPI.transfer(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    uint32_t results = resultsW1 + (resultsW2 << 8) + (resultsW3 << 16);
    return results;
}