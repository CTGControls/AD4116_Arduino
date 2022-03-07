#ifndef AD4116READ_H
#define AD4116READ_H
#include <Arduino.h>

    uint8_t AD4116_read(uint8_t ChipSelectPin, uint8_t comms);
    uint16_t AD4116_read16(uint8_t ChipSelectPin, uint8_t comms);
    uint32_t AD4116_read24(uint8_t ChipSelectPin, uint8_t comms);

#endif