#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoMqttClient.h>
#include <SD.h>

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

byte mac[] = {
  0xFB, 0xAE, 0x03, 0x36, 0xBC, 0x28
};
IPAddress ip(10, 40, 20, 93);
IPAddress dns(10, 40, 20, 1);
IPAddress gateway(10, 40, 20, 1);
IPAddress subnet(255, 255, 254, 0);

EthernetClass ethernet;
EthernetServer server(80);

SPISettings SPI_SETTING_AD4116(14000000, MSBFIRST, SPI_MODE3);
SPISettings SPI_Settings_Network(14000000, MSBFIRST, SPI_MODE0);

void setup() {

    // Main setting 
    Serial.begin(19200);

    // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip, dns, gateway, subnet);

    // start the server
    // server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());

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

    
    // Grt IP ADDRESS
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());


    Serial.println("___");
}


/* Read Chip Address 0x00
IPAddress ethernet_readIP(int ChipSelectPin)
{
    IPAddress ret;
	SPI.beginTransaction(Network_SPI_Settings);
	W5100.getIPAddress(ret.raw_address());
	SPI.endTransaction();
	return ret;
}
*/

/* Read Chip Address 0x00*/
uint8_t AD4116_readStatus(int ChipSelectPin)
{
return AD4116_read(ChipSelectPin, B01000000);
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

uint16_t AD4116_writeChannelOffset(uint8_t ChipSelectPin, uint8_t channel){

    if (!AD4116_isReady || channel < 0 || channel > 6) {
        return 1;
    }
    return 0;
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


uint8_t AD4116_write(uint8_t ChipSelectPin, byte comms)
{

    pinMode(ChipSelectPin,OUTPUT);
    
    delay(50);
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    
    digitalWrite(ChipSelectPin,LOW); //enable device

    delay(150);

    SPI.transfer(comms);
    unsigned int results = SPI.transfer(0x00);
    
    digitalWrite(ChipSelectPin,HIGH); //disable device

    return results;
}


uint8_t ethernetCheckConnection(uint8_t ChipSelectPin){

    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        return 1;
    }
    if (Ethernet.linkStatus() != LinkON) {
        Serial.println("Ethernet cable is not connected.");
        return 2;
    }

  return 0;
}


