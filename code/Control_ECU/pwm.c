/*
 ============================================================================
 Name        : pwm.c
 Author      : Aziza Zamel
 Description : Source file for the Timer0 PWM Mode Driver
 Date        : 4/10/2024
 ============================================================================
 */
#include "pwm.h"
#include "ATmega32_Registers.h"
#include "gpio.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize Timer0 in PWM mode and sets the required duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0_REG.byte = 0;											/* Set Timer Initial Value to 0 */

	OCR0_REG.byte = (uint8)(duty_cycle/100.0 *TIMER0_MAX_COMPARE_VALUE);	/* Set Compare value */

	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);

	TCCR0_REG.bits.FOC0_bit = LOGIC_LOW;				/* Fast PWM mode FOC0=0 */
	TCCR0_REG.bits.WGM00_bit = LOGIC_HIGH;				/* Fast PWM Mode WGM01=1 & WGM00=1 */
	TCCR0_REG.bits.WGM01_bit = LOGIC_HIGH;
	TCCR0_REG.bits.COM0_bits = 2;                       /* Clear OC0 when match occurs (non inverted mode) COM01=1 & COM00=0 */
	TCCR0_REG.bits.CS0_bits = TIMER0_CLOCK_SOURCE;		/* Select the clock source */

}

