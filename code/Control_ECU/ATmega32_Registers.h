/*
 ============================================================================
 Name        : ATmega32_Registers.h
 Author      : Aziza Zamel
 Description : Header file for ATmega32 Registers Declaration
 Date        : 25/9/2024
 ============================================================================
 */


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_

#include "ATmega32_register_unions.h"


/*********************************** GPIO Registers Definitions ********************************/
#define PORTA_REG     (*(volatile GPIO_Reg_Type * const)0x3B)
#define DDRA_REG      (*(volatile GPIO_Reg_Type * const)0x3A)
#define PINA_REG      (*(volatile const GPIO_Reg_Type * const)0x39)

#define PORTB_REG     (*(volatile GPIO_Reg_Type * const)0x38)
#define DDRB_REG      (*(volatile GPIO_Reg_Type * const)0x37)
#define PINB_REG      (*(volatile const GPIO_Reg_Type * const)0x36)

#define PORTC_REG     (*(volatile GPIO_Reg_Type * const)0x35)
#define DDRC_REG      (*(volatile GPIO_Reg_Type * const)0x34)
#define PINC_REG      (*(volatile const GPIO_Reg_Type * const)0x33)

#define PORTD_REG     (*(volatile GPIO_Reg_Type * const)0x32)
#define DDRD_REG      (*(volatile GPIO_Reg_Type * const)0x31)
#define PIND_REG      (*(volatile const GPIO_Reg_Type * const)0x30)
/***********************************************************************************************/


/*********************************** ADC Registers Definitions ********************************/
#define ADMUX_REG     (*(volatile ADC_ADMUX_Type * const)0x27)
#define ADCSRA_REG    (*(volatile ADC_ADCSRA_Type * const)0x26)
#define ADC_REG       (*(volatile ADC_Data_Type * const)0x24)
/***********************************************************************************************/

#define SREG_REG     (*(volatile SREG_Type * const)0x5F)

/***********************************************************************************************/



/*********************************** Timers Registers Definitions ******************************/

#define TIFR_REG      (*(volatile Timers_TIFR_Type * const)0x58)
#define TIMSK_REG     (*(volatile Timers_TIMSK_Type * const)0x59)

/*********************************** Timer0 Registers Definitions ******************************/
#define TCCR0_REG     (*(volatile Timer0_TCCR0_Type * const)0x53)
#define TCNT0_REG     (*(volatile Timer0_TCNT0_Type * const)0x52)
#define OCR0_REG     (*(volatile Timer0_OCR0_Type * const)0x5C)


/*********************************** Timer1 Registers Definitions ******************************/
#define TCNT1_REG     (*(volatile Timer1_TCNT1_Type * const)0x4C)
#define TCCR1A_REG    (*(volatile Timer1_TCCR1A_Type * const)0x4F)
#define TCCR1B_REG    (*(volatile Timer1_TCCR1B_Type * const)0x4E)
#define OCR1A_REG     (*(volatile Timer1_OCR1A_Type * const)0x4A)
#define OCR1B_REG     (*(volatile Timer1_OCR1B_Type * const)0x48)
#define ICR1_REG      (*(volatile Timer1_ICR1_Type * const)0x46)


/*********************************** Timer2 Registers Definitions ******************************/
#define TCCR2_REG     (*(volatile Timer2_TCCR2_Type * const)0x45)
#define TCNT2_REG     (*(volatile Timer2_TCNT2_Type * const)0x44)
#define OCR2_REG     (*(volatile Timer2_OCR2_Type * const)0x43)


/***********************************************************************************************/

/*********************************** UART Registers Definitions ******************************/
#define UDR_REG     (*(volatile UART_UDR_Type * const)0x2C)
#define UCSRA_REG     (*(volatile UART_UCSRA_Type * const)0x2B)
#define UCSRB_REG     (*(volatile UART_UCSRB_Type * const)0x2A)
#define UCSRC_REG     (*(volatile UART_UCSRC_Type * const)0x40)
#define UBRRL_REG     (*(volatile UART_UBRRL_Type * const)0x29)
#define UBRRH_REG     (*(volatile UART_UBRRH_Type * const)0x40)
/***********************************************************************************************/



/*********************************** SPI Registers Definitions ******************************/
#define SPCR_REG     (*(volatile SPI_SPCR_Type * const)0x2D)
#define SPSR_REG     (*(volatile SPI_SPSR_Type * const)0x2E)
#define SPDR_REG     (*(volatile SPI_SPDR_Type * const)0x2F)
/***********************************************************************************************/



/*********************************** TWI Registers Definitions ******************************/
#define TWBR_REG     (*(volatile TWI_TWBR_Type * const)0x20)
#define TWCR_REG     (*(volatile TWI_TWCR_Type * const)0x56)
#define TWSR_REG     (*(volatile TWI_TWSR_Type * const)0x21)
#define TWDR_REG     (*(volatile TWI_TWDR_Type * const)0x23)
#define TWAR_REG     (*(volatile TWI_TWAR_Type * const)0x22)
/***********************************************************************************************/



#define TWIE_BIT_POSITION 0
#define TWEN_BIT_POSITION 2
#define TWWC_BIT_POSITION 3
#define TWSTO_BIT_POSITION 4
#define TWSTA_BIT_POSITION 5
#define TWEA_BIT_POSITION 6
#define TWINT_BIT_POSITION 7


#define UCSZ0_BIT_POSITION 1
#define USBS_BIT_POSITION  3
#define UPM0_BIT_POSITION  4
#define UMSEL_BIT_POSITION 6
#define URSEL_BIT_POSITION 7

#endif /* ATMEGA32_REGISTERS_H_ */
