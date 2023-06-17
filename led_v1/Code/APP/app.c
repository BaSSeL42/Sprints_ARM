
#include "LSTD_TYPES.h"
#include "mgpio_Interface.h"
#include "led.h"
#include "button.h"
#include "app.h"

static void delay_ms(uint32_ number_of_seconds);

void APP_vidInit(void)
{

}


void APP_vidStart(void)
{

	return;
}



static void delay_ms(uint32_ number_of_seconds)
{
    // Converting time into milli_seconds
    uint32_ i,j;
	
	for (i = 0; i < number_of_seconds; i++)
	{
		for (j = 0; j < 1275; j++)
		{
			__asm__("NOP");
			
		}
	}
}





















