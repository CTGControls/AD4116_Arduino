#include "AD4116_Fuctions.h"



/* Read Chip Address 0x00*/
uint8_t AD4116_readStatus(SPIClass& spi, uint8_t ChipSelectPin)
{
return AD4116_read(spi,ChipSelectPin, B01000000);
}

/* Read Chip Address 0x00 Bit 7*/
boolean AD4116_isReady(SPIClass& spi, uint8_t ChipSelectPin){
    uint8_t status = AD4116_readStatus(spi, ChipSelectPin);
    if (bitRead(status,7)){
        return true;
    }
    return false;
}

/* Read Chip Address 0x06*/
uint16_t AD4116_readGPOIConfig(SPIClass& spi, uint8_t ChipSelectPin){
    return AD4116_read16(spi, ChipSelectPin, B01000110);
}

/* Read Chip Address 0x07*/
uint16_t AD4116_readID(SPIClass& spi, uint8_t ChipSelectPin)
{
return AD4116_read16(spi, ChipSelectPin, B01000111);
}

uint8_t AD4116_writeChannelSetup(SPIClass& spi, uint8_t ChipSelectPin, uint8_t channel){

    if (!AD4116_isReady || channel < 0 || channel > 6) {
        return 1;
    }
    return 0;
}

uint8_t AD4116_writeChannelOffset(SPIClass& spi, uint8_t ChipSelectPin, uint8_t channel, uint32_t offset){

    if (channel < 0 || channel > 6) {
        return 1;
    }
    
    uint8_t comms;

    switch (channel)
    {
        case 0:
        {
            comms= B00110000;
            break;
        }
        case 1:
        {
            comms= B00110001;
            break;
        }
        case 2:
        {
            comms= B00110010;
            break;
        }
        case 3:
        {
            comms= B00110011;
            break;
        }
        case 4:
        {
            comms= B00110100;
            break;
        }
        case 5:
        {
            comms= B00110101;
            break;
        }
        case 6:
        {
            comms= B00110110;
            break;
        }
        case 7:
        {
            comms= B00110111;
            break;
        }
                                    
    }
    uint8_t data[3];
    data[1] = (offset >> 16) & 0xFF;
    data[2] = (offset >> 8) & 0xFF;
    data[3] = (offset >> 0) & 0xFF;


    AD4116_write(spi, ChipSelectPin, comms, data);

    return 0;
}