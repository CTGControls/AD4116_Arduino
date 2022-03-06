#include <SPI.h>
#include <Wire.h> 
#include <ArduinoMqttClient.h>

#define DATAOUT 11 //COPI
#define DATAIN  12 //CIPO
#define SPICLOCK  13 //sck
#define CHIPSELECT10 10 //cs
#define CHIPSELECT09 9 //cs
#define CHIPSELECT06 6 //cs
#define CHIPSELECT05 5 //cs

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

#define BITMASK_SET(x, mask) ((x) |= (mask))
#define BITMASK_CLEAR(x, mask) ((x) &= (~(mask)))
#define BITMASK_FLIP(x, mask) ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x, mask) (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x, mask) ((x) & (mask))


void setup() {

  /* Main setting */
    Serial.begin(19200);

    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(CHIPSELECT10,OUTPUT);
    pinMode(CHIPSELECT09,OUTPUT);
    pinMode(CHIPSELECT06,OUTPUT);
    pinMode(CHIPSELECT05,OUTPUT);
    digitalWrite(CHIPSELECT10,HIGH); //disable device
    digitalWrite(CHIPSELECT09,HIGH); //disable device
    digitalWrite(CHIPSELECT06,HIGH); //disable device
    digitalWrite(CHIPSELECT05,HIGH); //disable device

    SPI.begin();
}

void loop() {

    if (AD4116_isReady){
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
        Serial.println(STATUS, BIN);

    } else {
        Serial.println("Not Ready");
    }

    Serial.println("___");
}   


/* Read Chip Address 0x00*/
uint8_t AD4116_readStatus(int ChipSelectPin)
{
return AD4116_read(B01000000, ChipSelectPin);
}

boolean AD4116_isReady(uint8_t ChipSelectPin){
    uint8_t status = AD4116_readStatus(ChipSelectPin);
    if (BIT_CHECK(status,7)){
        return true;
    }
    return false;
}

/* Read Chip Address 0x07*/
uint16_t AD4116_readID(uint8_t ChipSelectPin)
{
return AD4116_read16(ChipSelectPin, B01000111);
}

/* Read Chip Address 0x07*/
uint16_t AD4116_readGPOIConfig(uint8_t ChipSelectPin)
{
return AD4116_read16(ChipSelectPin, B01000110);
}


uint16_t AD4116_writeChannelSetup(uint8_t ChipSelectPin, uint8_t channel){

    if (!AD4116_isReady || channel < 0 || channel > 6) {
        return 1;
    }

    

    return 0;
}




uint8_t AD4116_read(uint8_t ChipSelectPin, uint8_t comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(5);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(50);

    SPI.transfer(comms);
    unsigned int results = SPI.transfer(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}


uint16_t AD4116_read16(uint8_t ChipSelectPin, uint8_t comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(5);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(50);

    SPI.transfer(comms);
    unsigned int results = SPI.transfer16(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}


uint8_t AD4116_write(int ChipSelectPin, byte comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(5);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(50);

    SPI.transfer(comms);
    unsigned int results = SPI.transfer(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}

