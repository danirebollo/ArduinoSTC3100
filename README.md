# arduino_stc3100 library
Library for stc3100 gas gauge based on the library from ST ( https://github.com/st-sw/STC3100_GenericDriver.git )

To use this library you need to connect the ESP32 board to STC3100 board using 4k7 pullup resistors on I2C pins, take note of this adjusts (or modify the source files with custom parameters if you want):

#define SENSERESISTOR  10 //¡¡10mR shunt resistor in the board!! take note that STEVAL-ISB009V1 uses 33mR. Use your own value
const uint8_t I2C_SDA_PIN = 21; //SDA;  // i2c SDA Pin
const uint8_t I2C_SCL_PIN = 22; //SCL;  // i2c SCL Pin

Please take note also that Vin MUST be <= Vcc. 
You can short VCC and VIN using the battery as VCC, but you CANNOT use 3V3 VCC from MCU board and measure a X>3.3V battery.  
https://electronics.stackexchange.com/questions/17463/help-on-stc3100-calculations

# examples
-stc3100_test
This is an Arduino example showing basic function of the library

-c_example
This is the example provided by ST

# docs
-STC3100
Application Note AN3064 - en.CD00248578: Using the STC3100 battery monitor for gas gauge applications
Application Note AN3395 - en.DM00027741: Sensing resistor selection and usage in STC310x battery monitoring applications
STC3100 datasheet - en.CD00219947: Datasheet

-STEVAL-ISB009V1 (STC3100 eval board)
Schematics, PCB, Gerber files and guidelines to develop a STC3100 evaluation board.

-charger-2-click
Another STC3100 board. You can get it here: https://www.digikey.es/products/en/development-boards-kits-programmers/evaluation-boards-expansion-boards-daughter-cards/797?k=STC3100 
https://www.mikroe.com/charger-2-click