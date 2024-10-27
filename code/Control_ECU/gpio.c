/*
 ============================================================================
 Name        : gpio.c
 Author      : Aziza Zamel
 Description : Source file for the AVR GPIO driver
 Date        : 25/9/2024
 ============================================================================
 */

#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "ATmega32_Registers.h" /* To use the IO Ports Registers */

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction) {
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/* Do Nothing */
	} else {
		/* Setup the pin direction as required */
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA_REG.byte, pin_num);
			} else {
				CLEAR_BIT(DDRA_REG.byte, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB_REG.byte, pin_num);
			} else {
				CLEAR_BIT(DDRB_REG.byte, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC_REG.byte, pin_num);
			} else {
				CLEAR_BIT(DDRC_REG.byte, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD_REG.byte, pin_num);
			} else {
				CLEAR_BIT(DDRD_REG.byte, pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		// Do Nothing
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTA_REG.byte, pin_num);
			} else {
				CLEAR_BIT(PORTA_REG.byte, pin_num);
			}
			break;
		case PORTB_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTB_REG.byte, pin_num);
			} else {
				CLEAR_BIT(PORTB_REG.byte, pin_num);
			}
			break;
		case PORTC_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTC_REG.byte, pin_num);
			} else {
				CLEAR_BIT(PORTC_REG.byte, pin_num);
			}
			break;
		case PORTD_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTD_REG.byte, pin_num);
			} else {
				CLEAR_BIT(PORTD_REG.byte, pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
		// Do Nothing
	} else {
		switch (port_num) {
		case PORTA_ID:
			return (uint8) GET_BIT(PINA_REG.byte, pin_num);
		case PORTB_ID:
			return (uint8) GET_BIT(PINB_REG.byte, pin_num);
		case PORTC_ID:
			return (uint8) GET_BIT(PINC_REG.byte, pin_num);
		case PORTD_ID:
			return (uint8) GET_BIT(PIND_REG.byte, pin_num);
		}
	}
	return LOGIC_LOW;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction) {
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS) {
		/* Do Nothing */
	} else {
		/* Setup the port direction as required */
		switch (port_num) {
		case PORTA_ID:
			DDRA_REG.byte = direction;
			break;
		case PORTB_ID:
			DDRB_REG.byte = direction;
			break;
		case PORTC_ID:
			DDRC_REG.byte = direction;
			break;
		case PORTD_ID:
			DDRD_REG.byte = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value) {
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS) {
		// Do Nothing
	} else {
		switch (port_num) {
		case PORTA_ID:
			PORTA_REG.byte = value;
			break;
		case PORTB_ID:
			PORTB_REG.byte = value;
			break;
		case PORTC_ID:
			PORTC_REG.byte = value;
			break;
		case PORTD_ID:
			PORTD_REG.byte = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num) {
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS) {
		// Do Nothing
	} else {
		switch (port_num) {
		case PORTA_ID:
			return PINA_REG.byte;
		case PORTB_ID:
			return PINB_REG.byte;
		case PORTC_ID:
			return PINC_REG.byte;
		case PORTD_ID:
			return PIND_REG.byte;
		}
	}
	return LOGIC_LOW;
}
