#ifndef AD4116FUCTIONS_H
#define AD4116FUCTIONS_H
#include <Arduino.h>
#include "AD4116_read.h"
#include "AD4116_write.h"
#include <SPI.h>

    /* Read Chip Address 0x00*/
    uint8_t AD4116_readStatus(SPIClass& spi, uint8_t ChipSelectPin);

    /* Read Chip Address 0x00 Bit 7*/
    boolean AD4116_isReady(SPIClass& spi, uint8_t ChipSelectPin);

    /* Read Chip Address 0x06*/
    uint16_t AD4116_readGPOIConfig(SPIClass& spi, uint8_t ChipSelectPin);

    /* Read Chip Address 0x07*/
    uint16_t AD4116_readID(SPIClass& spi, uint8_t ChipSelectPin);

    uint8_t AD4116_writeChannelSetup(SPIClass& spi, uint8_t ChipSelectPin, uint8_t channel);

    uint8_t AD4116_writeChannelOffset(SPIClass& spi, uint8_t ChipSelectPin, uint8_t channel, uint32_t offset);


#endif