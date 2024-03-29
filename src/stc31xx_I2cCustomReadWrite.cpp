/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
* File Name          : stc31xx_I2cCustomReadWrite.c
* Author             : AMS - AAS application
* Version            : V2
* Date               : 2014/10
* Description        : gas gauge firmware for STC31xx
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stc31xx_I2cCustomReadWrite.h"
#include <arduino.h>
#include <Wire.h>


/* Local Define ------------------------------------------------------------------*/
#define STC3100_SLAVE_ADDRESS_8BIT       0xE0   /* STC3100 8-bit address byte */
#define STC3100_SLAVE_ADDRESS_7BIT       0x70   /* STC3100 7-bit address byte */
#define NBRETRY 2

byte address=0x70; //E0
/* -----------------------------------------------------------------
The STC3100 routines use these I2C primitives 
to comunicate with device at address u8_I2C_address (see i2c.h):
I2c_CustomInit();
STC3100_Read(u8_NumberOfBytes, u8_RegAddress , pu8_RxBuffer);
STC3100_Write(u8_NumberOfBytes, u8_RegAddress , pu8_TxBuffer);
----------------------------------------------------------------- */

int I2c_CustomInit(void)
{
	Wire.setClock(100000);
  	Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
	return 0;
}

/*******************************************************************************
* Function Name  : STC3100_Write
* Description    : utility function to write several bytes to STC3100 registers
* Return         : error status
*******************************************************************************/

int STC3100_Write(unsigned char ByteCount, unsigned char RegisterAddr , unsigned char * TxBuffer)
{
	int Status = STC31xx_I2C_ERROR;
	int retry;

	for (retry=0; retry < NBRETRY; retry++)
	{  
		Wire.beginTransmission(address);
		Wire.write(RegisterAddr);   
		int i=0;
		for (i=0; i < ByteCount; i++)
		{ 
			Wire.write(TxBuffer[i]);   
		}
		Wire.endTransmission();
		Status = STC31xx_I2C_OK;

		if(Status != STC31xx_I2C_OK)
		{
			//printf("I2C write error\n");
		}
		else
		{
			break; //exit loop
		}
	}

	return Status;
}


/*******************************************************************************
* Function Name  : STC3100_Read
* Description    : utility function to read several bytes from STC3100 registers
* Return         : error status
*******************************************************************************/

int STC3100_Read(unsigned char ByteCount, unsigned char RegisterAddr , unsigned char * RxBuffer)
{
	int Status = STC31xx_I2C_ERROR;
	int retry;


	if (RxBuffer == (void*)0 ) 
		Status = STC31xx_I2C_ERR_BUFFER;
	else
	{
		for (retry=0; retry < NBRETRY; retry++)
		{
			//TODO: add your I2C function
			//Status = MyI2cRead(I2cBusNumber, STC31xx_SLAVE_ADDRESS_8BIT, RegisterAddr, RxBuffer, ByteCount);

			Wire.beginTransmission(address);    // Get the slave's attention, tell it we're sending a command byte
			Wire.write(RegisterAddr);  
			Wire.endTransmission(false); 
			Wire.requestFrom((int)address,(int)ByteCount);    // request 6 bytes from slave device #2
			int i=0;
  			while(Wire.available())    // slave may send less than requested
  			{
    			char c = Wire.read();    // receive a byte as character
				RxBuffer[i]=c;
				i++;
  			}
			Wire.endTransmission(); 
			Status = STC31xx_I2C_OK;

			if(Status != STC31xx_I2C_OK)
			{
				//printf("I2C read error\n");
			}
			else
			{
				break; //exit loop
			}
		}
	}

	return Status;
}

/* ---- end of I2C primitive interface --------------------------------------------- */
