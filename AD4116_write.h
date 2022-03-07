#ifndef AD4116WRITE_H
#define AD4116WRITE_H
#include <Arduino.h>
#include <SPI.h>

    //uint8_t AD4116_write(uint8_t ChipSelectPin, uint8_t comms);
    uint8_t AD4116_write(SPIClass& spi, uint8_t ChipSelectPin, uint8_t comms, byte data[]);

#endif