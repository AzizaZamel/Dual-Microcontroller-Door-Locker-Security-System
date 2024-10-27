/*
 ============================================================================
 Name        : timer.h
 Author      : Aziza Zamel
 Description : Header file for Timer Driver
 Date        : 22/10/2024
 ============================================================================
 */
#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	TIMER0_ID,TIMER1_ID,TIMER2_ID
}Timer_ID_Type;

typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,
	F_TIMER2_CPU_8=2,F_TIMER2_CPU_32,F_TIMER2_CPU_64,F_TIMER2_CPU_128,F_TIMER2_CPU_256,F_TIMER2_CPU_1024
}Timer_ClockType;

typedef enum{
	OVERFLOW_MODE,COMPARE_MODE=2
}Timer_ModeType;

typedef struct {
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue;
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;
} Timer_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initialize the required timer by:
 * 1. Setup Timer initial value.
 * 2. Setup Timer compare value in case of compare mode.
 * 3. Select the required prescaler
 * 4. Enable Overflow Interrupt or Compare Match Interrupt
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*
 * Description:  Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID_Type timer_type);

/*
 * Description: Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );

#endif /* TIMER_H_ */
