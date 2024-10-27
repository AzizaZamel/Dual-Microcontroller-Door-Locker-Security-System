/*
 ============================================================================
 Name        : timer.c
 Author      : Aziza Zamel
 Description : Header file for Timer Driver
 Date        : 22/10/2024
 ============================================================================
 */
#include "timer.h"
#include "ATmega32_Registers.h"
#include "avr/interrupt.h"
#include "common_macros.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back functions in the application */
static volatile void (*g_timer0CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_timer1CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_timer2CallBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect){
	if(g_timer0CallBackPtr != NULL_PTR){
		/* Call the Call Back function */
		(*g_timer0CallBackPtr)();
	}
}

ISR(TIMER0_COMP_vect){
	if (g_timer0CallBackPtr != NULL_PTR) {
		/* Call the Call Back function */
		(*g_timer0CallBackPtr)();
	}
}

ISR(TIMER1_OVF_vect){
	if(g_timer1CallBackPtr != NULL_PTR){
		/* Call the Call Back function */
		(*g_timer1CallBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_timer1CallBackPtr != NULL_PTR){
		/* Call the Call Back function */
		(*g_timer1CallBackPtr)();
	}
}

ISR(TIMER2_OVF_vect){
	if(g_timer2CallBackPtr != NULL_PTR){
		/* Call the Call Back function */
		(*g_timer2CallBackPtr)();
	}
}

ISR(TIMER2_COMP_vect){
	if(g_timer2CallBackPtr != NULL_PTR){
		/* Call the Call Back function */
		(*g_timer2CallBackPtr)();
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the required timer by:
 * 1. Setup Timer initial value.
 * 2. Setup Timer compare value in case of compare mode.
 * 3. Set the required clock.
 * 4. Enable Overflow Interrupt or Compare Match Interrupt
 */
void Timer_init(const Timer_ConfigType * Config_Ptr){
	switch(Config_Ptr->timer_ID){
	case TIMER0_ID:
		/* Set Timer0 initial count */
		TCNT0_REG.byte = (uint8) (Config_Ptr->timer_InitialValue);

		if(Config_Ptr->timer_mode == COMPARE_MODE){
			/* Set Timer0 compare value */
			OCR0_REG.byte = (uint8) (Config_Ptr->timer_compare_MatchValue);
			/* Enable Timer0 Compare Match Interrupt */
			TIMSK_REG.Bits.OCIE0_bit = LOGIC_HIGH;

		}else{
			/* Enable Timer0 Overflow Interrupt */
			TIMSK_REG.Bits.TOIE0_bit = LOGIC_HIGH;

		}
		/* Non PWM mode FOC0=1 */
		TCCR0_REG.bits.FOC0_bit = LOGIC_HIGH;

		/* Select the required mode
		 * for normal mode: WGM00=0 , WGM01=0
		 * for CTC mode:    WGM00=0 , WGM01=1
		*/
		TCCR0_REG.bits.WGM00_bit = LOGIC_LOW;
		TCCR0_REG.bits.WGM01_bit = GET_BIT(Config_Ptr->timer_mode,1);

		/*  Normal port operation, OC0 disconnected */
		TCCR0_REG.bits.COM0_bits = LOGIC_LOW;

		/* Select the required clock */
		TCCR0_REG.bits.CS0_bits = Config_Ptr->timer_clock;
		break;
	case TIMER1_ID:
		/* Set Timer1 initial count */
		TCNT1_REG.TwoBytes = Config_Ptr->timer_InitialValue;

		if(Config_Ptr->timer_mode == COMPARE_MODE){
			/* Set Timer1 compare value */
			OCR1A_REG.TwoBytes = Config_Ptr->timer_compare_MatchValue;
			/* Enable Timer1  Output Compare A Match Interrupt  */
			TIMSK_REG.Bits.OCIE1A_bit = LOGIC_HIGH;

		}else{
			/* Enable Timer1 Overflow Interrupt */
			TIMSK_REG.Bits.TOIE1_bit = LOGIC_HIGH;

		}

		/*  Normal port operation, OC1A disconnected */
		TCCR1A_REG.Bits.COM1A_bits = LOGIC_LOW;

		/* Non PWM mode FOC1A=1 */
		TCCR1A_REG.Bits.FOC1A_bit = LOGIC_HIGH;

		/* Select the required mode
		 * for normal mode: WGM10=0 , WGM11=0 , WGM12=0 , WGM13=0
		 * for CTC mode:    WGM10=0 , WGM11=0 , WGM12=1 , WGM13=0
		 */
		TCCR1A_REG.Bits.WGM10_bit = LOGIC_LOW;
		TCCR1A_REG.Bits.WGM11_bit = LOGIC_LOW;
		TCCR1B_REG.Bits.WGM12_bit = GET_BIT(Config_Ptr->timer_mode,1);
		TCCR1B_REG.Bits.WGM13_bit = LOGIC_LOW;

		/* Select the required clock */
		TCCR1B_REG.Bits.CS1_bits = Config_Ptr->timer_clock;
		break;
	case TIMER2_ID:
		/* Set Timer2 initial count */
		TCNT2_REG.byte = (uint8) (Config_Ptr->timer_InitialValue);

		if(Config_Ptr->timer_mode == COMPARE_MODE){
			/* Set Timer2 compare value */
			OCR2_REG.byte = (uint8) (Config_Ptr->timer_compare_MatchValue);
			/* Enable Timer2 Compare Match Interrupt */
			TIMSK_REG.Bits.OCIE2_bit = LOGIC_HIGH;

		}else{
			/* Enable Timer2 Overflow Interrupt */
			TIMSK_REG.Bits.TOIE2_bit = LOGIC_HIGH;

		}
		/* Non PWM mode FOC2=1 */
		TCCR2_REG.bits.FOC2_bit = LOGIC_HIGH;

		/* Select the required mode
		 * for normal mode: WGM20=0 , WGM21=0
		 * for CTC mode:    WGM20=0 , WGM21=1
		*/
		TCCR2_REG.bits.WGM20_bit = LOGIC_LOW;
		TCCR2_REG.bits.WGM21_bit = GET_BIT(Config_Ptr->timer_mode,1);

		/*  Normal port operation, OC2 disconnected */
		TCCR2_REG.bits.COM2_bits = LOGIC_LOW;

		/* Select the required clock */
		TCCR2_REG.bits.CS2_bits = Config_Ptr->timer_clock;
	}
}


/*
 * Description:  Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID_Type timer_type){
	switch(timer_type){
	case TIMER0_ID:

		/* Clear All Timer0 Registers */
		TCCR0_REG.byte = 0;
		TCNT0_REG.byte = 0;
		OCR0_REG.byte = 0;

		/* Disable Timer0 interrupt */
		TIMSK_REG.Bits.OCIE0_bit = LOGIC_LOW;
		TIMSK_REG.Bits.TOIE0_bit = LOGIC_LOW;

		/* Reset the global pointer value */
		g_timer0CallBackPtr = NULL_PTR;
		break;
	case TIMER1_ID:

		/* Clear All Timer1 Registers */
		TCCR1B_REG.Byte = 0;
		TCCR1A_REG.Byte = 0;
		TCNT1_REG.TwoBytes = 0;
		OCR1A_REG.TwoBytes = 0;

		/* Disable Timer1 interrupt */
		TIMSK_REG.Bits.OCIE1A_bit = LOGIC_LOW;
		TIMSK_REG.Bits.TOIE1_bit = LOGIC_LOW;

		/* Reset the global pointer value */
		g_timer1CallBackPtr = NULL_PTR;
		break;
	case TIMER2_ID:

		/* Clear All Timer2 Registers */
		TCCR2_REG.byte = 0;
		TCNT2_REG.byte = 0;
		OCR2_REG.byte = 0;

		/* Disable Timer2 interrupt */
		TIMSK_REG.Bits.OCIE2_bit = LOGIC_LOW;
		TIMSK_REG.Bits.TOIE2_bit = LOGIC_LOW;

		/* Reset the global pointer value */
		g_timer2CallBackPtr = NULL_PTR;
	}
}


/*
 * Description: Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID ){
	/* Save the address of the Call back function in a global variable */
	switch(a_timer_ID){
	case TIMER0_ID:
		g_timer0CallBackPtr = a_ptr;
		break;
	case TIMER1_ID:
		g_timer1CallBackPtr = a_ptr;
		break;
	case TIMER2_ID:
		g_timer2CallBackPtr = a_ptr;
	}
}


























