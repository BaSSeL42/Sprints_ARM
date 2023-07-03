
#ifndef MCAL_WDT_INTERFACE_H_
#define MCAL_WDT_INTERFACE_H_

#include "LSTD_TYPES.h"




#define WDT_INDEX_MAX			(2U)


typedef enum
{
	WDT_INDEX_0 = 0,
	WDT_INDEX_1 = 1,
	
	WDT_INDEX_INVALID
	
}en_wdt_index_t;



typedef enum
{
	WDT_NORMAL_INT = 0,
	WDT_NMI_INT		 = 1,
	WDT_DISABLE_INT = 2,
	
	WDT_INT_INVALID
	
}en_wdt_int_mode_t;


typedef struct
{
	en_wdt_index_t   		en_wdt_index;   		/* knowing wdt0 or wdt1 */
	uint32_ 				 		u32_timeout_ms; 		/* time in milli second */
	boolean					 		bool_wdt_mode;			/* pass TRUE to stop wdt while debugging */
	boolean							bool_reset_mode;   	/* pass TRUE to enable reset */
	en_wdt_int_mode_t		en_wdt_int_mode;		/* Interrupt type (Normal / NMI) */
	ptr_func_t					ptr_func_cbk;				/* Set call back function */
	
}st_wdt_cfg_t;




uint8_ WDT_u8Init(st_wdt_cfg_t* st_wdt_cfg);


uint8_ WDT_u8Reset(en_wdt_index_t en_wdt_index);


uint8_ WDT_u8DeInit(en_wdt_index_t en_wdt_index);



void WDT_vidDeInit(en_wdt_index_t en_wdt_index);



#endif /*MCAL_WDT_INTERFACE_H_*/