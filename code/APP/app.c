
#include "LSTD_TYPES.h"
#include "wdt_Interface.h"
#include "app.h"



static void delay_ms(uint32_ number_of_seconds);

st_wdt_cfg_t  st_wdt_0; 

static void APP_vidCBK(void);


void APP_vidInit(void)
{

		st_wdt_0.en_wdt_index 		= WDT_INDEX_0;
		st_wdt_0.bool_reset_mode	= FALSE;
		st_wdt_0.u32_timeout_ms		= 1000;
		st_wdt_0.bool_wdt_mode		= TRUE;
		st_wdt_0.en_wdt_int_mode	= WDT_NMI_INT;
		st_wdt_0.ptr_func_cbk			= APP_vidCBK;
	
		(void) WDT_u8Init(&st_wdt_0 );
	
	while(1);
}


void APP_vidStart(void)
{

	WDT_u8Reset(WDT_INDEX_0);
	
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

static void APP_vidCBK(void)
{
	while(1);
}





















