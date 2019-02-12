#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "INTERRUPTS_interface.h"
#include "LCD_interface.h"
#include "CLOCK_interface.h"

void main(void) {

	TIMER0_vidInit(TIMER0_COM_NORMAL,TIMER0_WGM_NORMAL,TIMER0_CLK_1);
	INTERRUPTS_vidSetInterruptEnable(INTERRUPTS_TOIE_0);
	INTERRUPTS_vidPutISRFunction(CLOCK_vidCount);
	INTERRUPTS_vidSetGlobalInterruptFlag();
	LCD_vidInit();

	while(1);
}
