
/********************************************************************************************************************
*												Standard Types LIB
********************************************************************************************************************/
#include "TM4C123.h"
#include "core_cm4.h"
#include "LBIT_MATH.h"
/********************************************************************************************************************
*												Peripheral Files
********************************************************************************************************************/
#include "wdt_private.h"
#include "wdt_Interface.h"
/********************************************************************************************************************
*												Global Static Variables
********************************************************************************************************************/
static uint32_ gl_a_u32_time_out[WDT_INDEX_MAX] = {0,0};
static volatile uint64_ gl_u64_wdt_ticks;
extern uint32_t SystemCoreClock;
static ptr_func_t gl_ptr_func_cbk = NULL;
/********************************************************************************************************************
*												Local Functions Prototype
********************************************************************************************************************/
static void set_wdt_ticks(en_wdt_index_t en_wdt_index, uint32_ u32_timeout_ms); 


/********************************************************************************************************************
 *  										Function Implementation
*******************************************************************************************************************/
uint8_ WDT_u8Init(st_wdt_cfg_t* st_wdt_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	if (st_wdt_cfg != NULL)
	{
		
		if ( 	st_wdt_cfg->en_wdt_index 		< WDT_INDEX_INVALID	&&
					st_wdt_cfg->en_wdt_int_mode < WDT_INT_INVALID		&&
					st_wdt_cfg->ptr_func_cbk 		!= NULL							&&
					st_wdt_cfg->u32_timeout_ms 	!= ZERO							&&
					st_wdt_cfg->bool_reset_mode < ERR_INVALID				&&
					st_wdt_cfg->bool_wdt_mode		<	ERR_INVALID					)
		{
			/* Enable Clock for wdt0 or wdt1 */
			/*-------------------------------*/
			SET_BIT(RCGCWD_REG , st_wdt_cfg->en_wdt_index); 
			
			/* converting time_ms into ticks and modified WDTLOAD register */
			/*-------------------------------------------------------------*/
			set_wdt_ticks(st_wdt_cfg->en_wdt_index  , st_wdt_cfg->u32_timeout_ms);
			
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
			if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
					while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );
			
			/* To enable reset Interrupt when wdt counts down to 0 */
			/*-----------------------------------------------------*/
			if (st_wdt_cfg->bool_reset_mode)
			{
				SET_BIT(WDTCTL(st_wdt_cfg->en_wdt_index) ,RESEN_IDX);
			}
			else 
			{
				CLR_BIT(WDTCTL(st_wdt_cfg->en_wdt_index) ,RESEN_IDX);
			}
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
			if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
					while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );
				
			if (st_wdt_cfg->en_wdt_int_mode == WDT_NORMAL_INT)
			{
			/* Set Interrupt to normal INT */
			/*-----------------------------*/
				CLR_BIT(WDTCTL(st_wdt_cfg->en_wdt_index) ,INTTYPE_IDX);
				
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
				if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
						while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );
				
				
			/*					 Enable Peripheral Interrupt 							*/
			/*-----------------------------------------------------*/					
				SET_BIT(WDTCTL(st_wdt_cfg->en_wdt_index) ,INTEN_IDX);
				
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
				if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
						while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );
				
			/* 					Enable NVIC IRQ					*/
			/*----------------------------------*/
				NVIC_EnableIRQ(WATCHDOG0_IRQn);
				
			/* Enable global Interrupt */
			/*-------------------------*/
				__enable_irq();
				
				
			}
			else if (st_wdt_cfg->en_wdt_int_mode == WDT_NMI_INT)
			{
			/* Set Interrupt to non maskable  INT */
			/*-------------------------------------*/
				SET_BIT(WDTCTL(st_wdt_cfg->en_wdt_index) ,INTTYPE_IDX);
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
				if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
						while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );
				
			/*					 Enable Peripheral Interrupt 							*/
			/*-----------------------------------------------------*/	
				SET_BIT(WDTCTL(st_wdt_cfg->en_wdt_index) ,INTEN_IDX);
				
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
				if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
						while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );

			/* Enable NVIC IRQ*/
			/*----------------*/
				NVIC_EnableIRQ(WATCHDOG0_IRQn);
				
			/* Enable global Interrupt */
			/*-------------------------*/
				__enable_irq();
			}
			else 
			{
				/* do nothing */
			}
			
			
			/* If STALL becoming true means the wdt will be stopped during depugging */
			/*-----------------------------------------------------------------------*/			
			if (st_wdt_cfg->bool_reset_mode)
			{
				SET_BIT( WDTTEST(st_wdt_cfg->en_wdt_index), STALL_IDX );
			}
			else 
			{
				CLR_BIT( WDTTEST(st_wdt_cfg->en_wdt_index), STALL_IDX );
				
			}
			
			/* If wdt1 is chosen wait until it synchronized with system clock */
			/*----------------------------------------------------------------*/
			if (st_wdt_cfg->en_wdt_index == WDT_INDEX_1)
					while( !( GET_BIT( WDTCTL(st_wdt_cfg->en_wdt_index) ,WRC_IDX) ) );
			
			/* 								Setting call back function 											*/
			/*----------------------------------------------------------------*/			
			gl_ptr_func_cbk = st_wdt_cfg->ptr_func_cbk;
			
		}
		else 
		{
			loc_u8_err_state = FAILED;
		}
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	
	return loc_u8_err_state;
}


uint8_ WDT_u8Reset(en_wdt_index_t en_wdt_index)
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (en_wdt_index < WDT_INDEX_INVALID)
	{
		if ( gl_a_u32_time_out[en_wdt_index] != 0 )
		{
			WDTLOAD(en_wdt_index) = gl_a_u32_time_out[en_wdt_index];	
		}
		else 
		{
			loc_u8_err_state = FAILED;
		}
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	
	return loc_u8_err_state;
}


uint8_ WDT_u8GetIntStatus(en_wdt_index_t en_wdt_index , boolean* ptr_bool_int_status)
{
	uint8_ loc_u8_err_state = FALSE;

	if (en_wdt_index < WDT_INDEX_INVALID && ptr_bool_int_status != NULL)
	{
		
		if ( GET_BIT(WDTRIS(en_wdt_index), WDTRIS_IDX ) )
		{
				*ptr_bool_int_status = TRUE;
		}
		else 
		{
			*ptr_bool_int_status = FALSE;
		}
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	
	return loc_u8_err_state;
}



uint8_ WDT_u8DeInit(en_wdt_index_t en_wdt_index)
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (en_wdt_index < WDT_INDEX_INVALID)
	{
				/* Disable Clock for wdt0 or wdt1 */
			/*-------------------------------*/
			SET_BIT(RCGCWD_REG , en_wdt_index); 
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	
	return loc_u8_err_state;
}


/********************************************************************************************************************
*												Local Functions Implementation
********************************************************************************************************************/
static void set_wdt_ticks(en_wdt_index_t en_wdt_index, uint32_ u32_timeout_ms)
{
	if (en_wdt_index < WDT_INDEX_INVALID && u32_timeout_ms != ZERO)
	{
		gl_u64_wdt_ticks = (uint64_) ( (u32_timeout_ms)* (SystemCoreClock/1000 ) );
		gl_a_u32_time_out[en_wdt_index] = (uint32_)gl_u64_wdt_ticks;
		
		WDTLOAD(en_wdt_index) = gl_a_u32_time_out[en_wdt_index];	
	}
	else 
	{
		/* do nothing */	
	}
}




/********************************************************************************************************************
*												IRQ Handler
********************************************************************************************************************/

void WDT0_Handler(void)
{
	if (gl_ptr_func_cbk != NULL)
	{
		gl_ptr_func_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void NMI_Handler(void)
{
	while(1);
	
}
