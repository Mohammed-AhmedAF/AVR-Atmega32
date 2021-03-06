/*
 * Author: Mohammed Ahmed Abd Al-Fattah
 * File: main.c
 * Purpose of project: The project allows storing IDs 
 * and passwords for 10 users and retreiving them from
 * EEPROM. After successful login, the user can control 
 * LED (on, off), and DC motor speed.
 */


#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "PASSWORD_interface.h"
#include "EEPROM_interface.h"
#include "PREPHIRALS_interface.h"

extern u8 u8PasswordMatch;
u8 u8UserChoice = 0;
void vidInit(void);
u8 u8LoginResult;

int main(void) {
	vidInit();
	while(1) {
		UART_vidSendString("1) Show ID, 2) Register ID, 3) Show count");
		UART_vidSendByte('\r');
		UART_vidSendString("4) Erase data 5) Login");
		UART_vidSendByte('\r');
		u8UserChoice = UART_u8ReceiveByte(); //Receiving user choice
		switch(u8UserChoice){
			case '1': //Show ID and password of all registered users
				PASSWORD_vidShowData();
				break;
			case '2': //Register a new user
				PASSWORD_vidRegisterID();
				PASSWORD_vidRegisterPassword();
				if (u8PasswordMatch == 1) {
					PASSWORD_vidSaveData();
				}
				break;
			case '3': //Show currently registered users
				PASSWORD_vidShowRegUsersCount();
				break;
			case '4': //To reset user count
				PASSWORD_vidEraseData();
				break;
			case '5': //Login, will ask user to enter ID and password
				u8LoginResult =	PASSWORD_vidLogin(); 
				if (u8LoginResult = PASSWORD_CORRECTPASSWORD) { //If password is correct
					PREPHIRALS_vidChoosePrephiral(); //Select motor or LED
				}
				break;
			default:
				UART_vidSendString("Invalid choice\r");
		}
	}
	return 0;
}

void vidInit(void) {
	UART_vidInit();
	EEPROM_vidInit();
	PREPHIRALS_vidInit();
}

