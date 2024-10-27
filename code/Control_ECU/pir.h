/*
 ============================================================================
 Name        : pir.h
 Author      : Aziza Zamel
 Description : Header file for the PIR sensor Driver
 Date        : 23/10/2024
 ============================================================================
 */
#ifndef PIR_H_
#define PIR_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* PIR HW Port and Pin Id */
#define PIR_PORT_ID		PORTC_ID
#define PIR_PIN_ID		PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initialize the PIR Driver.
 */
void PIR_init(void);


/*
 * Description :
 * Function responsible for return PIR State.
 */
uint8 PIR_getState(void);


#endif /* PIR_H_ */
