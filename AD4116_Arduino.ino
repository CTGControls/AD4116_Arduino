#include <SPI.h>
#include "AD4116_Fuctions.h"




#define DATAOUT 11 //COPI
#define DATAIN  12 //CIPO
#define SPICLOCK  13 //sck
#define CHIPSELECT10 10 //cs
#define CHIPSELECT09 9 //cs
#define CHIPSELECT06 6 //cs
#define CHIPSELECT05 5 //cs
#define CHIPSELECT04 4 //cs

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

/* a=target variable, s=start bit, l=length of bits */
#define BIT_GET(a,s,l) (((1 << l) - 1) & (a >> (s - 1)))

#define BITMASK_SET(x, mask) ((x) |= (mask))
#define BITMASK_CLEAR(x, mask) ((x) &= (~(mask)))
#define BITMASK_FLIP(x, mask) ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x, mask) (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x, mask) ((x) & (mask))



#include <SPI.h>

void setup() {
    // Main setting 
    Serial.begin(19200);


    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(CHIPSELECT10,OUTPUT);
    pinMode(CHIPSELECT09,OUTPUT);
    pinMode(CHIPSELECT06,OUTPUT);
    pinMode(CHIPSELECT05,OUTPUT);
    pinMode(CHIPSELECT04,OUTPUT);
    digitalWrite(CHIPSELECT10,HIGH); //disable device
    digitalWrite(CHIPSELECT09,HIGH); //disable device
    digitalWrite(CHIPSELECT06,HIGH); //disable device
    digitalWrite(CHIPSELECT05,HIGH); //disable device
    digitalWrite(CHIPSELECT04,HIGH); //disable device

    SPI.begin();

  }


void loop() {

    uint16_t ID = AD4116_readID(CHIPSELECT05);
    Serial.print("ID: ");
    Serial.println(ID, HEX);

    uint8_t STATUS = AD4116_readStatus(CHIPSELECT05);
    Serial.print("Status: ");
    Serial.println(STATUS, BIN);
    Serial.print("Ready: ");
    Serial.println(BIT_CHECK(STATUS,7));

    uint16_t GPOIConfig = AD4116_readGPOIConfig(CHIPSELECT05);
    Serial.print("GPOIConfig: ");
    Serial.println(GPOIConfig, BIN);


    uint32_t ChannelOneOffset = AD4116_read24(CHIPSELECT05, B01110000);;
    Serial.print("ChannelOneOffset: ");
    Serial.println(ChannelOneOffset, BIN);

    Serial.println("___");     
           
}



