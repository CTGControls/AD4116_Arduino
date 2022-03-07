#include "AD4116_Fuctions.h"
#include <SPI.h>


/* Read Chip Address 0x00*/
uint8_t AD4116_readStatus(int ChipSelectPin)
{
return AD4116_read(ChipSelectPin, B01000000);
}

/* Read Chip Address 0x00 Bit 7*/
boolean AD4116_isReady(uint8_t ChipSelectPin){
    uint8_t status = AD4116_readStatus(ChipSelectPin);
    if (bitRead(status,7)){
        return true;
    }
    return false;
}

/* Read Chip Address 0x06*/
uint16_t AD4116_readGPOIConfig(uint8_t ChipSelectPin)
{
return AD4116_read16(ChipSelectPin, B01000110);
}

/* Read Chip Address 0x07*/
uint16_t AD4116_readID(uint8_t ChipSelectPin)
{
return AD4116_read16(ChipSelectPin, B01000111);
}

/* Read Chip Address 0x07*/
uint16_t AD4116_writeChannelSetup(uint8_t ChipSelectPin, uint8_t channel){

    if (!AD4116_isReady || channel < 0 || channel > 6) {
        return 1;
    }
    return 0;
}

uint16_t AD4116_writeChannelOffset(uint8_t ChipSelectPin, uint8_t channel){

    if (!AD4116_isReady || channel < 0 || channel > 6) {
        return 1;
    }
    return 0;
}