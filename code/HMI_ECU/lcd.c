/*
 ============================================================================
 Name        : lcd.c
 Author      : Aziza Zamel
 Description : Source file for the LCD driver
 Date        : 1/10/2024
 ============================================================================
 */

#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include <stdlib.h>
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command) {
	/* Instruction Mode RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 3));

#elif (LCD_DATA_BITS_MODE == 8)

	/* out the required command to the data bus D0 --> D7 */
	GPIO_writePort(LCD_DATA_PORT_ID, command);

#endif
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 character) {
	/* Data Mode RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(character, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(character, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(character, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(character, 7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(character, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(character, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(character, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(character, 3));

#elif (LCD_DATA_BITS_MODE == 8)

	/* out the required character to the data bus D0 --> D7 */
	GPIO_writePort(LCD_DATA_PORT_ID, character);

#endif
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 8-bits.
 */
void LCD_init(void) {
	/* configure RS pin as output pin */
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	/* configure E pin as output pin */
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

	_delay_ms(20); /* LCD Power ON delay always > 15ms */

#if (LCD_DATA_BITS_MODE == 4)

	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)

	/* configure data pins as output pins */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	/* cursor off */
	LCD_sendCommand(LCD_CURSOR_OFF);
	/* clear LCD at the beginning */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const uint8 *str) {
	while (*str) {
		/* Display each character of the string */
		LCD_displayCharacter(*str++);
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row, uint8 col) {
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch (row) {
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = 0x40 + col;
		break;
	case 2:
		lcd_memory_address = 0x10 + col;
		break;
	case 3:
		lcd_memory_address = 0x50 + col;
	}

	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const uint8 *str) {
	/* Go to the required position */
	LCD_moveCursor(row, col);
	/* display the string */
	LCD_displayString(str);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(sint32 data) {
	/* String to hold the ASCII result */
	uint8 buff[16];

	/* convert integer to ASCII */
	itoa(data, (char*)buff, 10);

	/* Display the string */
	LCD_displayString(buff);
}

/*
 * Description :
 * Display the required float value on the screen
 */
void LCD_floatToString(float32 data) {
	/* Buffer to hold the resulting string */
	uint8 buff[16];

	/* Convert float to string with 2 decimal precision */
	dtostrf(data, 0, 2, (char*) buff);

	/* Display the string */
	LCD_displayString(buff);
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void) {
	/* Send clear display command */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

