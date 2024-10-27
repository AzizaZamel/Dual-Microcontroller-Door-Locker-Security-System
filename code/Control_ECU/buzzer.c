/*
 ============================================================================
 Name        : buzzer.c
 Author      : Aziza Zamel
 Description : Source file for the buzzer Driver
 Date        : 4/10/2024
 ============================================================================
 */
#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void) {
	/* configure buzzer pin as output pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	/* Turn off the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * Function responsible for Activate the buzzer.
 */
void Buzzer_on(void) {
	/* Turn on the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 * Function responsible for Deactivate the buzzer.
 */
void Buzzer_off(void) {
	/* Turn off the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
