 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 14 - 6 - 2023
 *  Description 			: systick_source.c --> APIs implementation
 *  Module Features		:
 *  											01- SYSTICK_u8Init()
 *  											02- SYSTICK_vidStart()
													03-	SYSTICK_vidResetTimer()
													04-	SYSTICK_vidStop()
													05-	SYSTICK_u8GetIntStatus()
													06-	SYSTICK_u8DeInit()
 *****************************************************************************/
 
/********************************************************************************************************************
*												Standard Types LIB
********************************************************************************************************************/
#include "TM4C123.h"
#include "LBIT_MATH.h"
/********************************************************************************************************************
*												Peripheral Files
********************************************************************************************************************/
#include "systick_Private.h"
#include "systick_Interface.h"
/********************************************************************************************************************
*												Global Static Variables
********************************************************************************************************************/
extern uint32_t SystemCoreClock;
static uint32_ gl_u32_time_out;
static uint8_	 gl_u8_is_initialized = FALSE;
static uint64_ gl_u64_wdt_ticks;
static ptr_func_t gl_pf_systk_cbk = NULL;

/********************************************************************************************************************
*												Local APIs Prototype
********************************************************************************************************************/
static void set_tick_time(uint32_ copy_u32_time_ms);


/********************************************************************************************************************
 *  										APIs Implementation
*******************************************************************************************************************/
/*****************************************************************************************************************
*											01- SYSTICK_u8Init()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Systick Timer Intialization
 * @in[1] 		: Address of struct Instance
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	SYSTICK_u8Init(st_systk_cfg_t* st_systk_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	if (st_systk_cfg != NULL)
	{
		if (	st_systk_cfg->en_systck_clk_src < SYSTK_CLK_SRC_INVALID		&&
					st_systk_cfg->en_systck_int			< SYSTK_IRQ_INVALID				&&
					st_systk_cfg->ptr_func					!= NULL										&&
					st_systk_cfg->u32_time_ms				!= 0)
		{
			STCURRENT_REG = 0;
			
			if(st_systk_cfg->en_systck_clk_src == SYSTK_SYSTEM_CLK)
			{
					SET_BIT( STCTRL_REG, CLK_SRC_IDX ); /* enable system clock */
			}
			else if(st_systk_cfg->en_systck_clk_src == SYSTK_PIOSC)
			{
					CLR_BIT( STCTRL_REG, CLK_SRC_IDX ); /* enable Precision internal oscillator clock */
			}
			else
			{
				/*do nothing  */
			}
			if (st_systk_cfg->en_systck_int	 == SYSTK_IRQ_ENABLE)
			{
					SET_BIT( STCTRL_REG, INTEN_IDX ); /* enable Interrupt */
			}
			else if(st_systk_cfg->en_systck_int	 == SYSTK_IRQ_DISABLE)
			{
					CLR_BIT( STCTRL_REG, INTEN_IDX ); /* Disable Interrupt */
			}
			else
			{
				/*do nothing  */
			}
			
			gl_pf_systk_cbk = st_systk_cfg->ptr_func;
			
			set_tick_time(st_systk_cfg->u32_time_ms);
			
			gl_u8_is_initialized = TRUE;
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

/*****************************************************************************************************************
*											02- SYSTICK_vidStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start Timer count
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ SYSTICK_vidStart(void)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	if (gl_u8_is_initialized == TRUE)
	{
		SET_BIT( STCTRL_REG, ENABLE_IDX ); /* enable Systick timer */
	}
	else
	{
		loc_u8_err_state = FAILED;
	}
	
	return loc_u8_err_state;
}

/*****************************************************************************************************************
*											03- SYSTICK_vidResetTimer()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Systick Reset Counter and start from beginning
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void SYSTICK_vidResetTimer(void)
{
	STCURRENT_REG = 0;
}


/*****************************************************************************************************************
*											04- SYSTICK_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop Systick Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void SYSTICK_vidStop(void)
{
	CLR_BIT( STCTRL_REG, ENABLE_IDX ); /* Disable Systick timer */
}



/*****************************************************************************************************************
*											05- SYSTICK_u8GetIntStatus()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get Systick Interrupt Flag to poll on it
 * @in[1] 		: p_u8_int_status
								- Address of Variable which interrupt state to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ SYSTICK_u8GetIntStatus(uint8_* p_u8_int_status )
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	if (p_u8_int_status != NULL)
	{
		*p_u8_int_status = GET_BIT(STCTRL_REG , COUNT_IDX);
	}
	else
	{
		loc_u8_err_state = FAILED;
	}
	
	return loc_u8_err_state;
	
}
/*****************************************************************************************************************
*											06- SYSTICK_u8DeInit()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: De-Initialize Systick Timer
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void SYSTICK_u8DeInit(void)
{
	STCTRL_REG &= 0xFFFFFFF8;
}


/********************************************************************************************************************
*												Local APIs Implementation
********************************************************************************************************************/
static void set_tick_time(uint32_ copy_u32_time_ms)
{
	
	gl_u64_wdt_ticks = (uint64_) ( (copy_u32_time_ms)* (SystemCoreClock/1000 ) );
	gl_u32_time_out = (uint32_)gl_u64_wdt_ticks;
	
	STRELOAD_REG = (gl_u32_time_out-1);
}





/********************************************************************************************************************
*												IRQ Handler
********************************************************************************************************************/


void SysTick_Handler(void)
{
	if (gl_pf_systk_cbk != NULL)
	{
		gl_pf_systk_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

