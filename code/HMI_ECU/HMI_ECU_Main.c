/*
 ============================================================================
 Name        : HMI_ECU_Main.c
 Author      : Aziza Zamel
 Description : Main Application for Human-Machine Interface (HMI_ECU)
 Date        : 23/10/2024
 ============================================================================
 */
#include "ATmega32_Registers.h"
#include "lcd.h"
#include "keypad.h"
#include "std_types.h"
#include "util/delay.h"
#include "uart.h"
#include "timer.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASSWORD_SIZE 				5
#define PASSWORD_SAVED 				0x11
#define DIFF_PASSWORDS				0x22
#define TRUE_PASSWORD				0x33
#define WRONG_PASSWORD				0x32
#define CONTROL_ECU_READY			0xFF
#define LOCKING_DOOR				0x44
#define UNLOCK_DOOR    				0x55
#define ALARM_MODE					0x53
#define CHANGE_PASSWORD				0xE3

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

volatile uint8 tick = 0;
volatile boolean t_15s_flag = FALSE;
volatile boolean t_60s_flag = FALSE;
volatile boolean alarm_flag = FALSE;
/* Create configuration structure for timer driver */
Timer_ConfigType timerConfig = {0,39062,TIMER1_ID,F_CPU_1024,COMPARE_MODE};


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void createPassword(void);
void getPassword(uint8 * pass, uint8 size);
void checkPassword(uint8* isPassTrue);
void alarmMode(void);
void timerCallBack(void);


/*******************************************************************************
 *                                    Main                                     *
 *******************************************************************************/

int main(void){
	uint8 key;
	uint8 isPassTrue;
	/* Create configuration structure for UART driver */
	UART_ConfigType uartConfig = {DATA_8_BIT,DISABLED,ONE_BIT,9600};

	/* Enable Global Interrupt */
	SREG_REG.bits.I_bit = LOGIC_HIGH;

	/* Initialize the UART driver with :
	 * Baud-rate = 9600 bits/sec
	 * one stop bit
	 * No parity
	 * 8-bit data
	 */
	UART_init(&uartConfig);
	/* Initialize the LCD */
	LCD_init();
	/* At the beginning, display "Door Lock System"  */
	LCD_displayString((uint8*)"Door Lock System");
	_delay_ms(500);

	/* when the system start for the first time, create New Password */
	createPassword();

	LCD_clearScreen();

	for(;;){
		/* Display always the main system options */
		LCD_displayString((uint8*)"+ : Open Door");
		LCD_displayStringRowColumn(1,0,(uint8*)"- : Change Pass");

		/* Get the key pressed by user */
		key = KEYPAD_getPressedKey();
		_delay_ms(250);
		/* if user chooses (+) Open Door */
		if(key == '+'){
			/* The user should enter the password saved in EEPROM */
			checkPassword(&isPassTrue);
			/* if the user entered the true password */
			if (isPassTrue == TRUE_PASSWORD) {
				/* Send UNLOCK_DOOR to the Control ECU to open the Door (rotate motor) */
				UART_sendByte(UNLOCK_DOOR);
				/* Set the Call back function pointer in the timer driver */
				Timer_setCallBack(timerCallBack, TIMER1_ID);
				/* Initialize the Timer driver :
				 * use timer 1
				 * prescaler 1024
				 * compare mode
				 * initial value = 0
				 * compare value = 39062, so the interrupt occurs every 5 seconds
				 */
				Timer_init(&timerConfig);

				/* Display Door Unlocking please wait on LCD for 15 seconds */
				LCD_clearScreen();
				LCD_displayString((uint8*) "Door Unlocking");
				LCD_displayStringRowColumn(1, 0, (uint8*) "please wait");
				 /* wait until t_15s_flag become true, this will happen after 15 seconds */
				while (t_15s_flag != TRUE);
				/* reset the flag */
				t_15s_flag = FALSE;

				/* Display wait for people to enter */
				LCD_clearScreen();
				LCD_displayString((uint8*) "wait for people");
				LCD_displayStringRowColumn(1, 0, (uint8*) "to enter");
				/* wait until Contro ECU sends LOCKING_DOOR */
				while (UART_recieveByte() != LOCKING_DOOR);

				/* Set the call back function and initialize timer driver again  */
				Timer_setCallBack(timerCallBack, TIMER1_ID);
				Timer_init(&timerConfig);

				/* Display Door Locking on LCD for 15 seconds */
				LCD_clearScreen();
				LCD_displayString((uint8*) "Door Locking");
				/* wait until t_15s_flag become true, this will happen after 15 seconds */
				while (t_15s_flag != TRUE);
				/* reset the flag */
				t_15s_flag = FALSE;
				LCD_clearScreen();
			}
			/* if the user entered wrong password 3 times */
			else if(isPassTrue == WRONG_PASSWORD){
				/* enter alarm mode for 1 minute */
				alarmMode();
			}

		}
		/* if user chooses (-) Change Password */
		else if(key == '-'){
			/* The user should enter the password saved in EEPROM */
			checkPassword(&isPassTrue);

			/* if the user entered the true password */
			if(isPassTrue == TRUE_PASSWORD){
				/* Send CHANGE_PASSWORD to the Control ECU to get ready to save new password */
				UART_sendByte(CHANGE_PASSWORD);
				/* Create new password */
				createPassword();
				LCD_clearScreen();
			}
			/* if the user entered wrong password 3 times */
			else if(isPassTrue == WRONG_PASSWORD){
				/* enter alarm mode for 1 minute */
				alarmMode();
			}
		}

	}
}

/*
 * Description :
 * Function responsible for :
 * 1. Display error message on LCD for 1 minute
 * 2. Wait for 1 minute and no inputs from the keypad will be accepted during this time period.
 */
void alarmMode(void){
	/* Set alarm flag */
	alarm_flag = TRUE;

	/* Set the call back function and initialize timer driver again  */
	Timer_setCallBack(timerCallBack, TIMER1_ID);
	Timer_init(&timerConfig);

	/* Display error message on LCD */
	LCD_clearScreen();
	LCD_displayString((uint8*)"System LOCKED");
	LCD_displayStringRowColumn(1,0,(uint8*)"Wait for 1 min");

	/* wait until t_60s_flag become true, this will happen after 1 minute */
	while(t_60s_flag != TRUE);
	/* reset the flag */
	t_60s_flag = FALSE;
	/* Reset alarm flag */
	alarm_flag = FALSE;
	LCD_clearScreen();
}

/*
 * Description :
 * Function responsible for :
 * 1. get the password from the user.
 * 2. send it to Control ECU.
 * 3. set a flag to  TRUE_PASSWORD if the user enters the true password
 *    or to WRONG_PASSWORD if the user enters a wrong password.
 */
void checkPassword(uint8* flag_ptr){
	uint8 size = PASSWORD_SIZE+2;
	uint8 pass[size] , loop_counter;

	/* loop 3 times each time get password from the user it true return */
	for(loop_counter = 0 ; loop_counter<3 ; loop_counter++){
		LCD_clearScreen();
		LCD_displayString((uint8*)"enter old pass:");
		LCD_moveCursor(1,0);

		/* Get the password from the user */
		getPassword(pass,size);
		/* wait until the user press enter button */
		while(KEYPAD_getPressedKey() != '=');
		_delay_ms(250);

		/* Wait until Control_ECU is ready to receive the password */
		while(UART_recieveByte() != CONTROL_ECU_READY);
		/* send the password */
		UART_sendString(pass);

		/* if the password is true Control_ECU will send TRUE_PASSWORD , if not it will sends WRONG_PASSWORD */
		*flag_ptr = UART_recieveByte();
		if(*flag_ptr == TRUE_PASSWORD){
			return;
		}
	} /* it will reach here if the user enters wrong password 3 times and then (*flag_ptr=WRONG_PASSWORD)  */
}

/*
 * Description :
 * Function responsible for create new password by:
 * 1. take the password from the user and take the password again for confirmation.
 * 2. send the two passwords to Control_ECU.
 * 3. it will repeat until the user enters the same password twice
 */
void createPassword(void){
	uint8 size = PASSWORD_SIZE+2;
	uint8 pass1[size], pass2[size];
	uint8 isSaved;
	/* loop until the user enters same password twice for confirmation */
	for(;;){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,(uint8*)"plz enter pass: ");
		LCD_moveCursor(1,0);

		/* Get the password from the user */
		getPassword(pass1,size);
		/* wait until the user press enter button */
		while(KEYPAD_getPressedKey() != '=');
		_delay_ms(250);

		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,(uint8*)"plz re-enter the");
		LCD_displayStringRowColumn(1,0,(uint8*)"same pass:");

		/* Get the password again from the user for confirmation */
		getPassword(pass2,size);
		/* wait until the user press enter button */
		while(KEYPAD_getPressedKey() != '=');
		_delay_ms(250);

		/* Wait until Control_ECU is ready to receive the password */
		while(UART_recieveByte() != CONTROL_ECU_READY);
		/* send the to passwords to Control_ECU */
		UART_sendString(pass1);
		UART_sendString(pass2);

		/* if the two passwords are the same Control_ECU will save the password in the EEPROM and send PASSWORD_SAVED */
		isSaved = UART_recieveByte();
		/* if Control_ECU saves the password return */
		if(isSaved == PASSWORD_SAVED){
			return;
		}
	}

}

/*
 * Description :
 * Function responsible for take password from user.
 */
void getPassword(uint8 * pass, uint8 size){
	uint8 loop_counter;
	for (loop_counter = 0; loop_counter < size-2; loop_counter++) {
		pass[loop_counter] = KEYPAD_getPressedKey() + 48;
		LCD_displayCharacter('*');
		_delay_ms(250);
	}
	/* end the password with # and null */
	pass[loop_counter++] = '#';
	pass[loop_counter] = '\0';
}

/*
 * Description :
 * call-back function.
 */
void timerCallBack(void){
	tick++;
	if((!alarm_flag) && (tick == 3)){
		t_15s_flag = TRUE;
		tick = 0;
		Timer_deInit(TIMER1_ID);
	}else if((alarm_flag) && (tick == 12)){
		t_60s_flag = TRUE;
		tick = 0;
		Timer_deInit(TIMER1_ID);
	}
}





