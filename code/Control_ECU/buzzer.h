/*
 ============================================================================
 Name        : buzzer.h
 Author      : Aziza Zamel
 Description : Header file for the buzzer Driver
 Date        : 4/10/2024
 ============================================================================
 */

#ifndef BUZZER_H_
#define BUZZER_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Buzzer HW Port and Pin Id */
#define BUZZER_PORT_ID		PORTC_ID
#define BUZZER_PIN_ID		PIN7_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initialize the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void);

/*
 * Description :
 * Function responsible for Activate the buzzer.
 */
void Buzzer_on(void);


/*
 * Description :
 * Function responsible for Deactivate the buzzer.
 */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
