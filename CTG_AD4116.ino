#include <SPI.h>

#define DATAOUT 11      // COPI
#define DATAIN 12       // CIPO
#define SPICLOCK 13     // sck
#define CHIPSELECT10 10 // cs
#define CHIPSELECT09 9  // cs
#define CHIPSELECT06 6  // cs
#define CHIPSELECT05 5  // cs
#define CHIPSELECT04 4  // cs


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

    SPI.begin();
}



void loop()
{

    uint16_t ID = AD4116_readID(CHIPSELECT05);
    Serial.print("ID: ");
    Serial.println(ID, HEX);

    uint8_t STATUS = AD4116_readStatus(CHIPSELECT05);
    Serial.print("Status: ");
    Serial.println(STATUS, BIN);
    Serial.print("Ready: ");
    Serial.println(bitRead(STATUS, 7));

    uint16_t GPOIConfig = AD4116_readGPOIConfig(CHIPSELECT05);
    Serial.print("GPOIConfig: ");
    Serial.println(GPOIConfig, BIN);

    uint32_t ChannelOneOffsetRead1 = AD4116_read24(CHIPSELECT05, 0b01110000);
    Serial.print("ChannelOneOffsetRead1: ");
    Serial.println(ChannelOneOffsetRead1, BIN);

    // if (ChannelOneOffsetRead1 == B10000000){
    //     uint8_t ChannelOneOffsetWrite = AD4116_writeChannelOffset(spi, 0, CHIPSELECT05, 0b10000001);
    // }else {
    //     uint8_t ChannelOneOffsetWrite = AD4116_writeChannelOffset(spi, 0, CHIPSELECT05, 0b10000000);
    // }

    uint32_t ChannelOneOffsetRead2 = AD4116_read24(CHIPSELECT05, 0b01110000);
    Serial.print("ChannelOneOffsetRead2: ");
    Serial.println(ChannelOneOffsetRead2, BIN);

    Serial.println("___");
}



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



/* Read Chip Address 0x00*/
uint8_t AD4116_readStatus(uint8_t ChipSelectPin)
{
return AD4116_read(ChipSelectPin, 0b01000000);
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
uint16_t AD4116_readGPOIConfig(uint8_t ChipSelectPin){
    return AD4116_read16(ChipSelectPin, 0b01000110);
}

/* Read Chip Address 0x07*/
uint16_t AD4116_readID(uint8_t ChipSelectPin)
{
return AD4116_read16(ChipSelectPin, 0b01000111);
}

// uint8_t AD4116_writeChannelSetup(uint8_t ChipSelectPin, uint8_t channel){

//     if (!AD4116_isReady || channel < 0 || channel > 6) {
//         return 1;
//     }
//     return 0;
// }

// uint8_t AD4116_writeChannelOffset(uint8_t ChipSelectPin, uint8_t channel, uint32_t offset){

//     if (channel < 0 || channel > 6) {
//         return 1;
//     }
    
//     uint8_t comms;

//     switch (channel)
//     {
//         case 0:
//         {
//             comms= 0b00110000;
//             break;
//         }
//         case 1:
//         {
//             comms= 0b00110001;
//             break;
//         }
//         case 2:
//         {
//             comms= 0b00110010;
//             break;
//         }
//         case 3:
//         {
//             comms= 0b00110011;
//             break;
//         }
//         case 4:
//         {
//             comms= 0b00110100;
//             break;
//         }
//         case 5:
//         {
//             comms= 0b00110101;
//             break;
//         }
//         case 6:
//         {
//             comms= 0b00110110;
//             break;
//         }
//         case 7:
//         {
//             comms= 0b00110111;
//             break;
//         }
                                    
//     }
//     uint8_t data[3];
//     data[1] = (offset >> 16) & 0xFF;
//     data[2] = (offset >> 8) & 0xFF;
//     data[3] = (offset >> 0) & 0xFF;


//     AD4116_write(spi, ChipSelectPin, comms, data);

//     return 0;
// }


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
