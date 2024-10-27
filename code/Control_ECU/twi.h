/*
 ============================================================================
 Name        : twi.h
 Author      : Aziza Zamel
 Description : Header file for I2C driver
 Date        : 20/10/2024
 ============================================================================
 */


#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef uint8 TWI_AddressType;

typedef uint8 TWI_BaudRateType;

 typedef struct{
	 TWI_AddressType address;
	 TWI_BaudRateType bit_rate;
 }TWI_ConfigType;


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*
  * Description :
  * Function responsible for Initialize the TWI device by:
  * 1. Setup TWI Bit Rate Register (TWBR) and the Prescaler bits.
  * 2. Enable the TWI.
  * 3. Setup my address if any master device want to call me.
  */
void TWI_init(TWI_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for send the start bit.
 */
void TWI_start(void);

/*
 * Description :
 * Function responsible for send the stop bit.
 */
void TWI_stop(void);

/*
 * Description :
 * Function responsible for write byte on the I2C bus.
 */
void TWI_writeByte(uint8 data);

/*
 * Description :
 * Function responsible for receive byte and send ACK.
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description :
 * Function responsible for receive byte without send ACK.
 */
uint8 TWI_readByteWithNACK(void);

/*
 * Description :
 * Function return the status of the TWI logic and the Two-wire Serial Bus.
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
