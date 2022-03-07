#include <SPI.h>
#include "AD4116_Fuctions.h"

#define DATAOUT 11      // COPI
#define DATAIN 12       // CIPO
#define SPICLOCK 13     // sck
#define CHIPSELECT10 10 // cs
#define CHIPSELECT09 9  // cs
#define CHIPSELECT06 6  // cs
#define CHIPSELECT05 5  // cs
#define CHIPSELECT04 4  // cs

#include <SPI.h>

SPIClass spi;

void setup()
{
    // Main setting
    Serial.begin(19200);

    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK, OUTPUT);
    pinMode(CHIPSELECT10, OUTPUT);
    pinMode(CHIPSELECT09, OUTPUT);
    pinMode(CHIPSELECT06, OUTPUT);
    pinMode(CHIPSELECT05, OUTPUT);
    pinMode(CHIPSELECT04, OUTPUT);
    digitalWrite(CHIPSELECT10, HIGH); // disable device
    digitalWrite(CHIPSELECT09, HIGH); // disable device
    digitalWrite(CHIPSELECT06, HIGH); // disable device
    digitalWrite(CHIPSELECT05, HIGH); // disable device
    digitalWrite(CHIPSELECT04, HIGH); // disable device

    //spi.begin();
}



void loop_old()
{

    uint16_t ID = AD4116_readID(spi, CHIPSELECT05);
    Serial.print("ID: ");
    Serial.println(ID, HEX);

    uint8_t STATUS = AD4116_readStatus(spi, CHIPSELECT05);
    Serial.print("Status: ");
    Serial.println(STATUS, BIN);
    Serial.print("Ready: ");
    Serial.println(bitRead(STATUS, 7));

    uint16_t GPOIConfig = AD4116_readGPOIConfig(spi, CHIPSELECT05);
    Serial.print("GPOIConfig: ");
    Serial.println(GPOIConfig, BIN);

    uint32_t ChannelOneOffsetRead1 = AD4116_read24(spi, CHIPSELECT05, B01110000);
    Serial.print("ChannelOneOffsetRead1: ");
    Serial.println(ChannelOneOffsetRead1, BIN);

    if (ChannelOneOffsetRead1 == B10000000){
        uint8_t ChannelOneOffsetWrite = AD4116_writeChannelOffset(spi, 0, CHIPSELECT05, B10000001);
    }else {
        uint8_t ChannelOneOffsetWrite = AD4116_writeChannelOffset(spi, 0, CHIPSELECT05, B10000000);
    }

    uint32_t ChannelOneOffsetRead2 = AD4116_read24(spi, CHIPSELECT05, B01110000);
    Serial.print("ChannelOneOffsetRead2: ");
    Serial.println(ChannelOneOffsetRead2, BIN);

    Serial.println("___");
}



