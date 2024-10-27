/*
 ============================================================================
 Name        : ATmega32_register_unions.h
 Author      : Aziza Zamel
 Description : Header file with union declarations for all ATmega32 registers,
               providing access to full register values and individual bits for peripheral control.
 Date        : 25/9/2024
 ============================================================================
 */

#ifndef ATMEGA32_REGISTER_UNIONS_H_
#define ATMEGA32_REGISTER_UNIONS_H_

#include "std_types.h"



typedef union {
	uint8 byte;
	struct {
		uint8 C_bit :1;
		uint8 Z_bit :1;
		uint8 N_bit :1;
		uint8 V_bit :1;
		uint8 S_bit :1;
		uint8 H_bit :1;
		uint8 T_bit :1;
		uint8 I_bit :1;
	} bits;
} SREG_Type;


/************************* GPIO type structure declarations ************************/

typedef union {
	uint8 byte;
	struct {
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} bits;
} GPIO_Reg_Type;

/***********************************************************************************************/


/************************* ADC Registers type structure declarations ************************/

typedef union {
	uint8 byte;
	struct {
		uint8 MUX_bits :5;
		uint8 ADLAR_bit :1;
		uint8 REFS_bits :2;
	} bits;
} ADC_ADMUX_Type;

typedef union {
	uint8 byte;
	struct {
		uint8 ADPS_bits :3;
		uint8 ADIE_bit :1;
		uint8 ADIF_bit :1;
		uint8 ADATE_bit :1;
		uint8 ADSC_bit :1;
		uint8 ADEN_bit :1;
	} bits;
} ADC_ADCSRA_Type;

typedef union {
	uint16 TwoBytes;
	struct {
		uint16 Bit0 :1;
		uint16 Bit1 :1;
		uint16 Bit2 :1;
		uint16 Bit3 :1;
		uint16 Bit :1;
		uint16 Bit5 :1;
		uint16 Bit6 :1;
		uint16 Bit7 :1;
		uint16 Bit8 :1;
		uint16 Bit9 :1;
		uint16 Bit10 :1;
		uint16 Bit11 :1;
		uint16 Bit12 :1;
		uint16 Bit13 :1;
		uint16 Bit14 :1;
		uint16 Bit15 :1;
	} Bits;
} ADC_Data_Type;


/***********************************************************************************************/



/************************* Timers Registers type structure declarations ************************/


typedef union {
	uint8 Byte;
	struct{
		uint8 TOIE0_bit:1;
		uint8 OCIE0_bit:1;
		uint8 TOIE1_bit:1;
		uint8 OCIE1B_bit:1;
		uint8 OCIE1A_bit:1;
		uint8 TICIE1_bit:1;
		uint8 TOIE2_bit:1;
		uint8 OCIE2_bit:1;
	}Bits;
}Timers_TIMSK_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 TOV0_bit:1;
		uint8 OCF0_bit:1;
		uint8 TOV1_bit:1;
		uint8 OCF1B_bit:1;
		uint8 OCF1A_bit:1;
		uint8 ICF1_bit:1;
		uint8 TOV2_bit:1;
		uint8 OCF2_bit:1;
	}Bits;
}Timers_TIFR_Type;



/************************* Timer0 Registers type structure declarations ************************/

typedef union {
	uint8 byte;
	struct {
		uint8 CS0_bits :3;
		uint8 WGM01_bit :1;
		uint8 COM0_bits :2;
		uint8 WGM00_bit :1;
		uint8 FOC0_bit :1;
	} bits;
} Timer0_TCCR0_Type;


typedef union {
	uint8 byte;
	struct {
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} bits;
} Timer0_TCNT0_Type;


typedef union {
	uint8 byte;
	struct {
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} bits;
} Timer0_OCR0_Type;





/************************* Timer1 Registers type structure declarations ************************/
typedef union {
	uint8 Byte;
	struct{
		uint8 WGM10_bit:1;
		uint8 WGM11_bit:1;
		uint8 FOC1B_bit:1;
		uint8 FOC1A_bit:1;
		uint8 COM1B_bits:2;
		uint8 COM1A_bits:2;
	}Bits;
}Timer1_TCCR1A_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 CS1_bits:3;
		uint8 WGM12_bit:1;
		uint8 WGM13_bit:1;
		uint8 :1;
		uint8 ICES1_bit:1;
		uint8 ICNC1_bit:1;
	}Bits;
}Timer1_TCCR1B_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_TCNT1_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_OCR1A_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_OCR1B_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0:1;
		uint16 Bit1:1;
		uint16 Bit2:1;
		uint16 Bit3:1;
		uint16 Bit:1;
		uint16 Bit5:1;
		uint16 Bit6:1;
		uint16 Bit7:1;
		uint16 Bit8:1;
		uint16 Bit9:1;
		uint16 Bit10:1;
		uint16 Bit11:1;
		uint16 Bit12:1;
		uint16 Bit13:1;
		uint16 Bit14:1;
		uint16 Bit15:1;
	}Bits;
}Timer1_ICR1_Type;




/************************* Timer2 Registers type structure declarations ************************/

typedef union {
	uint8 byte;
	struct {
		uint8 CS2_bits :3;
		uint8 WGM21_bit :1;
		uint8 COM2_bits :2;
		uint8 WGM20_bit :1;
		uint8 FOC2_bit :1;
	} bits;
} Timer2_TCCR2_Type;


typedef union {
	uint8 byte;
	struct {
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} bits;
} Timer2_TCNT2_Type;


typedef union {
	uint8 byte;
	struct {
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} bits;
} Timer2_OCR2_Type;


/***********************************************************************************************/


/************************* UART Registers type structure declarations ************************/

typedef union {
	uint8 Byte;
	struct{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	}Bits;
}UART_UDR_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 MPCM_bit :1;
		uint8 U2X_bit :1;
		uint8 PE_bit :1;
		uint8 DOR_bit :1;
		uint8 FE_bit :1;
		uint8 UDRE_bit :1;
		uint8 TXC_bit :1;
		uint8 RXC_bit :1;
	}Bits;
}UART_UCSRA_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 TXB8_bit :1;
		uint8 RXB8_bit :1;
		uint8 UCSZ2_bit :1;
		uint8 TXEN_bit :1;
		uint8 RXEN_bit :1;
		uint8 UDRIE_bit :1;
		uint8 TXCIE_bit :1;
		uint8 RXCIE_bit :1;
	}Bits;
}UART_UCSRB_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 UCPOL_bit :1;
		uint8 UCSZ_2bits :2;
		uint8 USBS_bit :1;
		uint8 UPM_bits :2;
		uint8 UMSEL_bit :1;
		uint8 URSEL_bit :1;
	}Bits;
}UART_UCSRC_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	}Bits;
}UART_UBRRL_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 UBRR_bits :4;
		uint8 :3;
		uint8 URSEL_bit :1;
	}Bits;
}UART_UBRRH_Type;


/***********************************************************************************************/


/************************* SPI Registers type structure declarations ************************/

typedef union {
	uint8 Byte;
	struct{
		uint8 SPR0_bit :1;
		uint8 SPR1_bit :1;
		uint8 CPHA_bit :1;
		uint8 CPOL_bit :1;
		uint8 MSTR_bit :1;
		uint8 DORD_bit :1;
		uint8 SPE_bit :1;
		uint8 SPIE_bit :1;
	}Bits;
}SPI_SPCR_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 SPI2X_bit :1;
		uint8 :5;
		uint8 WCOL_bit :1;
		uint8 SPIF_bit :1;
	}Bits;
}SPI_SPSR_Type;



typedef union {
	uint8 Byte;
	struct{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	}Bits;
}SPI_SPDR_Type;

/***********************************************************************************************/


/************************* TWI/I2C Registers type structure declarations ************************/

typedef union {
	uint8 Byte;
	struct{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	}Bits;
}TWI_TWBR_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 TWIE_bit :1;
		uint8 :1;
		uint8 TWEN_bit :1;
		uint8 TWWC_bit :1;
		uint8 TWSTO_bit :1;
		uint8 TWSTA_bit :1;
		uint8 TWEA_bit :1;
		uint8 TWINT_bit :1;
	}Bits;
}TWI_TWCR_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 TWPS_bits :2;
		uint8 :1;
		uint8 TWS_bits :5;
	}Bits;
}TWI_TWSR_Type;


typedef union {
	uint8 Byte;
	struct{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	}Bits;
}TWI_TWDR_Type;

typedef union {
	uint8 Byte;
	struct{
		uint8 TWGCE :1;
		uint8 TWA :7;
	}Bits;
}TWI_TWAR_Type;

/***********************************************************************************************/

#endif /* ATMEGA32_REGISTER_UNIONS_H_ */
