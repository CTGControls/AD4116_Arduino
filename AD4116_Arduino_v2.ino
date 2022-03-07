#include <Arduino.h>
#include "ad411x_regs.h"


#define CHIPSELECT05 5  // cs
#define DATAOUT 11      // COPI
#define DATAIN 12       // CIPO
#define SPICLOCK 13     // sck



#include <SPI.h>

SPIClass spi;
ad717x_dev *my_ad7176_2;
ad717x_init_param ad7176_2_init;


void setup()
{
    // Main setting
    Serial.begin(19200);




    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK, OUTPUT);
    pinMode(CHIPSELECT05, OUTPUT);

    ad7176_2_init.spi_init.chip_select = CHIPSELECT05;
    ad7176_2_init.spi_init.device_id = 0;
    ad7176_2_init.spi_init.max_speed_hz = 1000000;
    ad7176_2_init.spi_init.mode = SPI_MODE_3;
    ad7176_2_init.regs = ad4111_regs;
    ad7176_2_init.num_regs = sizeof(ad4111_regs) / sizeof(ad4111_regs[0]);



}




void loop_old()
{


    /* Other variables */
    int32_t timeout = 1000;
    int32_t ret;
    int32_t sample;

    /* Initialize the driver instance and let's use the ad7176_2_regs array defined in ad7176_2_regs.h */
    Serial.println(AD717X_Init(&my_ad7176_2, ad7176_2_init));
    if (ret < 0){}
        /* Something went wrong, check the value of ret! */
    
    /* Read data from the ADC */
    Serial.println(AD717X_WaitForReady(my_ad7176_2, timeout));
    if (ret < 0){}
        /* Something went wrong, check the value of ret! */
    
    Serial.println(AD717X_ReadData(my_ad7176_2, &sample));
    if (ret < 0){}
            /* Something went wrong, check the value of ret! */
}



