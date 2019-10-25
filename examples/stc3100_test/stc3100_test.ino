
#include <Wire.h>
#include <stc3100.h>
#include <stc31xx_I2cCustomReadWrite.h>

int status;

void setup()
{
	// Serial
	Serial.begin(115200);
	Serial.println("start gas gauge\n");

	I2c_CustomInit();
	if (STC3100_Startup() != 0)
	{
		//handle error
		Serial.println("STC3100_Startup error!!");
	}
}

void loop()
{	
	doMeasure();
	delay(1000);
}
void doMeasure()
{
	int LoopCount = 10; //arbitrary value for example
	byte error, address;
	int nDevices;
	// read the data from the STC3100, converts the raw values to user units.
	printf("ReadBatteryData\n");
	status = ReadBatteryData();

	if (status == STC3100_OK)
	{
		/* results available */
		printf("Battery:: voltage (mV): %d. ", s16_BattVoltage);
		printf("current (mA): %d. ", s16_BattCurrent);
		printf("temperature (0.1C): %d. ", s16_BattTemperature);
		printf("C count (mAh): %d. ", s16_BattChargeCount);
		printf("C count RAW (mAh): %d,%d. ", s16_BattChargeCountRAW, s16_BattChargeCountRAW2);
		printf("convertion counter: %d\n", s16_BattCounter);
		printf("\n");
	}
	else //error occured
	{
		printf("Error with ReadBatteryData: %d\n", status);
	}

	//status = STC3100_Powerdown();	// stops and puts the STC3100 in power down
	//if( status != STC3100_OK)  return -1; //error
}