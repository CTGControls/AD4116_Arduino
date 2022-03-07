#ifndef AD4116FUCTIONS_H
#define AD4116FUCTIONS_H
#include <Arduino.h>
#include "AD4116_read.h"
#include "AD4116_write.h"

    /* Read Chip Address 0x00*/
    uint8_t AD4116_readStatus(int ChipSelectPin);

    /* Read Chip Address 0x00 Bit 7*/
    boolean AD4116_isReady(uint8_t ChipSelectPin);

    /* Read Chip Address 0x06*/
    uint16_t AD4116_readGPOIConfig(uint8_t ChipSelectPin);

    /* Read Chip Address 0x07*/
    uint16_t AD4116_readID(uint8_t ChipSelectPin);



#endif