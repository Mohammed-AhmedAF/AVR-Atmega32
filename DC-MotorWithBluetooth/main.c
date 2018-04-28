
/* Name: Mohamed Ahmed Abd Al-Fattah Mahmoud
 * Date: 28-4-2018 (First completion)
 * Update: Make a DC motor speed controller with Bluetooth.
 * There are six speeds (1,2,3,4,5,6).
 * Send the key corresponding to the speed to make
 * the DC motor rotate on that spead.
 */

#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER1_interface.h"
#include "UART_interface.h"

void vidInit(void);
void vidSelectSpeed(void);

u16 u16Count;
u16 u16Speeds_Array[6] = {700,600,500,400,300,200};
void (*ptrFunc) (void);
u8 u8keyPressed;

int main(void) {	
	vidInit();
	UART_vidInit();
	while(1) {
		vidSelectSpeed();	
	}
	return 0;
}

void vidInit(void) {
	DIO_vidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); //Output pin for OC1A
	TIMER1_vidInit(TIMER1_WGM_FPWM_OCR,TIMER1_COM1A_CLEAR,TIMER1_COM1B_NORMAL,TIMER1_CLK_1);
	TIMER1_vidSetOCRA(600);
}

void vidSelectSpeed(void) {
	do {
		u8keyPressed = UART_u8ReceiveByte();
		if (u8keyPressed == '1') {
			TIMER1_vidSetOCRA(u16Speeds_Array[0]);
		}
		else if (u8keyPressed == '2') {
			TIMER1_vidSetOCRA(u16Speeds_Array[1]);
		}
		else if (u8keyPressed == '3') {
			TIMER1_vidSetOCRA(u16Speeds_Array[2]);
		}
		else if (u8keyPressed == '4') {
			TIMER1_vidSetOCRA(u16Speeds_Array[3]);
		}
		else if (u8keyPressed == '5') {
			TIMER1_vidSetOCRA(u16Speeds_Array[4]);
		}
		else if (u8keyPressed == '6') {
			TIMER1_vidSetOCRA(u16Speeds_Array[5]);
		}	
	}while(1);
}