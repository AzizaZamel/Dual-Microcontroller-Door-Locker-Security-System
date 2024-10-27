/*
 ============================================================================
 Name        : pir.c
 Author      : Aziza Zamel
 Description : Source file for the PIR sensor Driver
 Date        : 23/10/2024
 ============================================================================
 */

#include "pir.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initialize the PIR Driver.
 */
void PIR_init(void){
	/* configure PIR pin as input pin */
	GPIO_setupPinDirection(PIR_PORT_ID,PIR_PIN_ID,PIN_INPUT);
}

/*
 * Description :
 * Function responsible for return PIR State.
 */
uint8 PIR_getState(void){
	return GPIO_readPin(PIR_PORT_ID,PIR_PIN_ID);
}
