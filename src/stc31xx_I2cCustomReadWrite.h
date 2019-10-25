#ifndef __STC3100CRW_H
#define __STC3100CRW_H

#define STC31xx_I2C_OK 0
#define STC31xx_I2C_ERROR 1
#define STC31xx_I2C_ERR_BUFFER 2

#include <arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

	int STC3100_Write(unsigned char ByteCount, unsigned char RegisterAddr , unsigned char * TxBuffer);
	int STC3100_Read(unsigned char ByteCount, unsigned char RegisterAddr , unsigned char * RxBuffer);
	int I2c_CustomInit(void);

	const uint8_t I2C_SDA_PIN = 21; //SDA;  // i2c SDA Pin
	const uint8_t I2C_SCL_PIN = 22; //SCL;  // i2c SCL Pin

#ifdef __cplusplus
}
#endif

#endif
