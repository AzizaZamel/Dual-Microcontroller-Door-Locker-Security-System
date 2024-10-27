/*
 ============================================================================
 Name        : pwm.h
 Author      : Aziza Zamel
 Description : Header file for the Timer0 PWM Mode Driver
 Date        : 4/10/2024
 ============================================================================
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TIMER0_NO_PRESCALER			1
#define TIMER0_PRESCALER_8 			2
#define TIMER0_PRESCALER_64			3
#define TIMER0_PRESCALER_256		4
#define TIMER0_PRESCALER_1024		5

#define TIMER0_CLOCK_SOURCE			TIMER0_PRESCALER_64
#define TIMER0_MAX_COMPARE_VALUE	255

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize Timer0 in PWM mode and sets the required duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
