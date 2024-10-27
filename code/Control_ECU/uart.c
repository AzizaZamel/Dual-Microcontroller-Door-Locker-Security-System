/*
 ============================================================================
 Name        : uart.h
 Author      : Aziza Zamel
 Description : Source file for UART AVR driver with RX complete interrupt only
 Date        : 14/10/2024
 ============================================================================
 */


#include "uart.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "ATmega32_Registers.h" /* To use the UART Registers */
#include "avr/interrupt.h"

#ifdef RX_INTERRUPT
volatile uint8 g_uartRecievedByte;
volatile boolean g_uartRecieveFlag = LOGIC_LOW;
ISR(USART_RXC_vect){
	g_uartRecievedByte = UDR_REG.Byte;
	g_uartRecieveFlag = LOGIC_HIGH;
}
#endif


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA_REG.Bits.U2X_bit = LOGIC_HIGH;


	UCSRB_REG.Byte = 0;
	/* Receiver Enable */
	UCSRB_REG.Bits.RXEN_bit = LOGIC_HIGH;
	/* Transmitter Enable */
	UCSRB_REG.Bits.TXEN_bit = LOGIC_HIGH;


#ifdef RX_INTERRUPT
	/* Enable USART RX Complete Interrupt Enable */
	UCSRB_REG.Bits.RXCIE_bit = LOGIC_HIGH;
#endif
	
	/*
	 * The URSEL must be one when writing the UCSRC
	 * insert the required character size
	 * Select Asynchronous Operation
	 * insert the required Stop bits one or two
	 * insert the required Parity type
	 */

	UCSRC_REG.Byte = (1 << URSEL_BIT_POSITION)
			| ((Config_Ptr->bit_data & 0x03) << UCSZ0_BIT_POSITION)
			| ((Config_Ptr->parity) << UPM0_BIT_POSITION)
			| ((Config_Ptr->stop_bit) << USBS_BIT_POSITION);


	/* Calculate the UBRR register value */
	ubrr_value = (uint16)( (F_CPU / ((Config_Ptr->baud_rate) * 8UL)) - 1 );

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH_REG.Byte = ubrr_value>>8;
	UBRRL_REG.Byte = ubrr_value;
}

/*
 * Description :
 * Function responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(UCSRA_REG.Bits.UDRE_bit == LOGIC_LOW){}
	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */

	UDR_REG.Byte = data;
}


#ifndef RX_INTERRUPT

/*
 * Description :
 * Function responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(UCSRA_REG.Bits.RXC_bit == LOGIC_LOW){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR_REG.Byte;
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

#endif


/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	/* Send the whole string */
	while(*Str != '\0')
	{
		UART_sendByte(*Str++);
	}		

}

