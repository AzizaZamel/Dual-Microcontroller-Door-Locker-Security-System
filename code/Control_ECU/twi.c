/*
 ============================================================================
 Name        : twi.c
 Author      : Aziza Zamel
 Description : Source file for I2C driver
 Date        : 20/10/2024
 ============================================================================
 */
#include "twi.h"

#include "ATmega32_Registers.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

 /*
  * Description :
  * Function responsible for Initialize the TWI device by:
  * 1. Setup TWI Bit Rate Register (TWBR) and the Prescaler bits.
  * 2. Enable the TWI.
  * 3. Setup my address if any master device want to call me.
  */
void TWI_init(TWI_ConfigType * Config_Ptr){

	/* Setup the given TWI Bit Rate Register (TWBR) */
	TWBR_REG.Byte = Config_Ptr -> bit_rate;
	/* prescaler value = 1 , TWPS0=0  TWPS1=0 */
	TWSR_REG.Bits.TWPS_bits = 0b00;

	/* Two Wire Bus address my address if any master device want to call me
	 * General Call Recognition: Off
	*/
	TWAR_REG.Bits.TWA = Config_Ptr -> address;
	TWAR_REG.Bits.TWGCE = LOGIC_LOW;

	/* Disable TWI Interrupt */
	TWCR_REG.Bits.TWIE_bit = LOGIC_LOW;
	/* enable TWI */
	TWCR_REG.Bits.TWEN_bit = LOGIC_HIGH;
}

/*
 * Description :
 * Function responsible for send the start bit.
 */
void TWI_start(void){
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = (1 << TWINT_BIT_POSITION) | (1 << TWSTA_BIT_POSITION) | (1 << TWEN_BIT_POSITION);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(TWCR_REG.Bits.TWINT_bit == LOGIC_LOW);
}


/*
 * Description :
 * Function responsible for send the stop bit.
 */
void TWI_stop(void){
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR_REG.Byte = (1 << TWINT_BIT_POSITION) | (1 << TWSTO_BIT_POSITION) | (1 << TWEN_BIT_POSITION);
}



/*
 * Description :
 * Function responsible for write byte on the I2C bus.
 */
void TWI_writeByte(uint8 data){

	/* Put data On TWI data Register */
	TWDR_REG.Byte = data;

    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR_REG.Byte = (1 << TWINT_BIT_POSITION) | (1 << TWEN_BIT_POSITION);

    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(TWCR_REG.Bits.TWINT_bit == LOGIC_LOW);
}

/*
 * Description :
 * Function responsible for receive byte and send ACK.
 */
uint8 TWI_readByteWithACK(void){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR_REG.Byte = (1 << TWINT_BIT_POSITION) | (1 << TWEN_BIT_POSITION) | (1 << TWEA_BIT_POSITION);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(TWCR_REG.Bits.TWINT_bit == LOGIC_LOW);
    /* Read Data */
    return TWDR_REG.Byte;
}


/*
 * Description :
 * Function responsible for receive byte without send ACK.
 */
uint8 TWI_readByteWithNACK(void){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR_REG.Byte = (1 << TWINT_BIT_POSITION) | (1 << TWEN_BIT_POSITION);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(TWCR_REG.Bits.TWINT_bit == LOGIC_LOW);
    /* Read Data */
    return TWDR_REG.Byte;
}


/*
 * Description :
 * Function return the status of the TWI logic and the Two-wire Serial Bus.
 */
uint8 TWI_getStatus(void){
    uint8 status;
    status = TWSR_REG.Bits.TWS_bits << 3;
    return status;
}










