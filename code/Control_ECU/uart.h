/*
 ============================================================================
 Name        : uart.h
 Author      : Aziza Zamel
 Description : Header file for UART AVR driver with RX complete interrupt only
 Date        : 14/10/2024
 ============================================================================
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

//#define RX_INTERRUPT

#ifdef RX_INTERRUPT
extern volatile uint8 g_uartRecievedByte;
extern volatile boolean g_uartRecieveFlag;
#endif
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef uint32   UART_BaudRateType;

typedef enum
{
	DISABLED,EVEN_PARITY=2,ODD_PARITY
}UART_ParityType;


typedef enum
{
	ONE_BIT,TWO_BITS
}UART_StopBitType;


typedef enum
{
	DATA_5_BIT,DATA_6_BIT,DATA_7_BIT,DATA_8_BIT,DATA_9_BIT=7
}UART_BitDataType;



typedef struct
{
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
}UART_ConfigType;




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Function responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
