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
********************************************************************************************************************/
/********************************************************************************************************************
*												Standard Types LIB
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
#include "TM4C123.h"
#include "core_cm4.h"
#include "LBIT_MATH.h"
/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*												Peripheral Files
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
#include "gpt_Private.h"
#include "gpt_Interface.h"
#include "gpt_Config.h"
/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*												Global Static Variables
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
extern uint32_t SystemCoreClock;
static en_gpt_time_x_t	gl_en_time_init 	= GPT_TIME_INVALID;
static en_gpt_ch_id_t		gl_en_channel_id	= GPT_CHANNEL_INVALID; 

static uint32_ gl_u32_is_initialized = FALSE;;
static uint64_ gl_u64_gpt_ticks;
static ptr_func_t gl_pf_gpt_ch0_cbk = NULL;
static ptr_func_t gl_pf_gpt_ch1_cbk = NULL;
static ptr_func_t gl_pf_gpt_ch2_cbk = NULL;
static ptr_func_t gl_pf_gpt_ch3_cbk = NULL;
static ptr_func_t gl_pf_gpt_ch4_cbk = NULL;
static ptr_func_t gl_pf_gpt_ch5_cbk = NULL;
static ptr_func_t gl_pf_gpt_ch6_cbk = NULL;
/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*												Local APIs Prototype
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
static void set_tick_time(en_gpt_ch_id_t copy_en_gpt_ch_id, uint32_ copy_u32_time);

/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
 *  										APIs Implementation
*******************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/

/*****************************************************************************************************************
*											01- GPT_u8Init()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Systick Timer Intialization
 * @in[1] 		: Address of struct Instance
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_u8Init(st_gpt_timer_cfg_t* st_gpt_timer_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	if (st_gpt_timer_cfg != NULL)
	{
		if (	st_gpt_timer_cfg->en_gpt_ch_id 			< 	GPT_CHANNEL_INVALID		&&
					st_gpt_timer_cfg->en_gpt_mode				< 	GPT_CH_MODE_INVALID		&&
					st_gpt_timer_cfg->en_gpt_irq				< 	GPT_IRQ_INVALID				&&
					st_gpt_timer_cfg->en_gpt_time_x			< 	GPT_TIME_INVALID			&&
					st_gpt_timer_cfg->ptr_func					!= 	NULL									&&
					st_gpt_timer_cfg->en_gpt_stall			< 	GPT_STALL_INVALID			&&
					st_gpt_timer_cfg->u32_set_time			!= 	ZERO)
		{
/*----*/					
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
/*----*/
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/			
			/*						Ensure the timer is disabled										*/
			/*-------------------------------------------------------------*/
			CLR_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TAEN_IDX);
			
			/*						Counting STOP/RUNNING during debugging					 */
			/*-------------------------------------------------------------*/		
			if (st_gpt_timer_cfg->en_gpt_stall == GPT_STALL_DISABLE)
			{
				CLR_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TASTALL_IDX);
			}
			else if(st_gpt_timer_cfg->en_gpt_stall == GPT_STALL_ENABLE)
			{
				SET_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TASTALL_IDX);
			}
			else 
			{
				/* do nothing */
			}
			
			/*						Choose Indvidual Mode										*/
			/*-------------------------------------------------------------*/			
			GPTMCFG_REG(st_gpt_timer_cfg->en_gpt_ch_id ) = 0x4;
			
			/*						GPT mode Selection (one shot / periodic)				 */
			/*-------------------------------------------------------------*/					
			if (st_gpt_timer_cfg->en_gpt_mode == GPT_CH_MODE_ONE_SHOT)
			{
				GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id) |= 0x1; 
			}
			else if(st_gpt_timer_cfg->en_gpt_mode == GPT_CH_MODE_PERIODIC)
			{
				GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id) |= 0x2; 
			}
			else
			{
				/* do nothing */
			}
			
			/*						Timer Counting Selection				 */
			/*-------------------------------------------------------------*/	
/*----*/
#if GPT_TIMER_COUNT_SELECTION == GPT_COUNT_DOWN
/*----*/				
			CLR_BIT(GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TACDIR_IDX  );
/*----*/			
#elif GPT_TIMER_COUNT_SELECTION == GPT_COUNT_UP
/*----*/				
			SET_BIT(GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TACDIR_IDX  );
/*----*/					
#else
/*----*/	
#error "please choose either (GPT_COUNT_DOWN or GPT_COUNT_UP)"
/*----*/	
#endif	
/*----*/
			/*						Set time count				 */
			/*-------------------------------------------------------------*/				
			if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_US)
			{
				gl_en_time_init = GPT_TIME_US;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_MS)
			{
				gl_en_time_init = GPT_TIME_MS;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_S)
			{
				gl_en_time_init = GPT_TIME_S;
			}
			else 
			{
				/* do nothing */
			}
			set_tick_time(st_gpt_timer_cfg->en_gpt_ch_id, st_gpt_timer_cfg->u32_set_time);
			
			/*						Set timer IRQ				 */
			/*-------------------------------------------------------------*/	
				
			if(st_gpt_timer_cfg->en_gpt_irq == GPT_IRQ_ENABLE)
			{
				SET_BIT( GPTMIMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TATOIM_IDX);
			}
			else if (st_gpt_timer_cfg->en_gpt_irq == GPT_IRQ_DISABLE)
			{
				SET_BIT( GPTMICR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TATOCINT_IDX);
			}
			else 
			{
				/* do nothing */
			}
			
			/*						Set }Call Back Function			 */
			/*-------------------------------------------------------------*/
			gl_pf_gpt_cbk = st_gpt_timer_cfg->ptr_func;
			
/*----*/	
#elif	GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/				
			/*todo: GPT_TIMER_B will be implemented*/
/*----*/				
#else
/*----*/
#error " please select either (GPT_TIMER_A , GPT_TIMER_B) "			
/*----*/				
#endif			
/*----*/		
/*----*/
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
			gl_en_channel_id = st_gpt_timer_cfg->en_gpt_ch_id;

			/*						Ensure the timer is disabled										*/
			/*-------------------------------------------------------------*/
//			CLR_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TAEN_IDX);
			GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) = 0x00000000;
			
			/*						Counting STOP/RUNNING during debugging					 */
			/*-------------------------------------------------------------*/		
			if (st_gpt_timer_cfg->en_gpt_stall == GPT_STALL_DISABLE)
			{
				//CLR_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TASTALL_IDX);
				
			}
			else if(st_gpt_timer_cfg->en_gpt_stall == GPT_STALL_ENABLE)
			{
				//SET_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TASTALL_IDX);
				GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) |= ((1U) << TASTALL_IDX);
			}
			else 
			{
				/* do nothing */
			}
			
			/*						Choose Concatination Mode										*/
			/*-------------------------------------------------------------*/			
			GPTMCFG_REG(st_gpt_timer_cfg->en_gpt_ch_id ) =  0x00000000;
			
			/*						GPT mode Selection (one shot / periodic)				 */
			/*-------------------------------------------------------------*/					
			if (st_gpt_timer_cfg->en_gpt_mode == GPT_CH_MODE_ONE_SHOT)
			{
				GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id) |= 0x1; 
			}
			else if(st_gpt_timer_cfg->en_gpt_mode == GPT_CH_MODE_PERIODIC)
			{
				GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id) |= 0x2; 
			}
			else
			{
				/* do nothing */
			}
			
			/*						Timer Counting Selection				 */
			/*-------------------------------------------------------------*/	
/*----*/
#if GPT_TIMER_COUNT_SELECTION == GPT_COUNT_DOWN
/*----*/		
			CLR_BIT(GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TACDIR_IDX  );
/*----*/		
#elif GPT_TIMER_COUNT_SELECTION == GPT_COUNT_UP
/*----*/		
			SET_BIT(GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TACDIR_IDX  );
/*----*/				
#else
/*----*/
			#error "please choose either (GPT_COUNT_DOWN or GPT_COUNT_UP)"
/*----*/
#endif	
/*----*/
			
			/*						Set time count				 */
			/*-------------------------------------------------------------*/				
			if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_US)
			{
				gl_en_time_init = GPT_TIME_US;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_MS)
			{
				gl_en_time_init = GPT_TIME_MS;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_S)
			{
				gl_en_time_init = GPT_TIME_S;
			}
			else 
			{
				/* do nothing */
			}
			set_tick_time(st_gpt_timer_cfg->en_gpt_ch_id, st_gpt_timer_cfg->u32_set_time);
			
			/*						Set timer IRQ				 */
			/*-------------------------------------------------------------*/		
			if(st_gpt_timer_cfg->en_gpt_irq == GPT_IRQ_ENABLE)
			{
			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMIMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TATOIM_IDX);
				
			/*						Enable NVIC Timer Interrupt			 */
			/*-------------------------------------------------------------*/				
				if (gl_en_channel_id == GPT_WIDE_CHANNEL_0)
					NVIC_EnableIRQ(TIMER0A_IRQn);
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_1)
					NVIC_EnableIRQ(TIMER1A_IRQn);
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_2)
					NVIC_EnableIRQ(TIMER2A_IRQn);
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_3)
					NVIC_EnableIRQ(TIMER3A_IRQn);
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_4)
					NVIC_EnableIRQ(TIMER4A_IRQn);
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_5)
					NVIC_EnableIRQ(TIMER5A_IRQn);
				else
				{
					/* do nothing */
				}
				
			/*						Enable Global Interrupt			 */
			/*-------------------------------------------------------------*/
			__enable_irq();				
			}
			else if (st_gpt_timer_cfg->en_gpt_irq == GPT_IRQ_DISABLE)
			{
				SET_BIT( GPTMICR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TATOCINT_IDX);
			}
			else 
			{
				/* do nothing */
			}
			
			/*						Set Call Back Function			 */
			/*-------------------------------------------------------------*/
			
				if (gl_en_channel_id == GPT_WIDE_CHANNEL_0)
					gl_pf_gpt_ch0_cbk = st_gpt_timer_cfg->ptr_func;
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_1)
					gl_pf_gpt_ch1_cbk = st_gpt_timer_cfg->ptr_func;
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_2)
					gl_pf_gpt_ch2_cbk = st_gpt_timer_cfg->ptr_func;
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_3)
					gl_pf_gpt_ch3_cbk = st_gpt_timer_cfg->ptr_func;
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_4)
					gl_pf_gpt_ch4_cbk = st_gpt_timer_cfg->ptr_func;
				else if(gl_en_channel_id == GPT_WIDE_CHANNEL_5)
					gl_pf_gpt_ch5_cbk = st_gpt_timer_cfg->ptr_func;
				else
				{
					/* do nothing */
				}
/*----*/
#else
/*----*/
#error "Invalid Timer please select either (GPT_TIMER_INDVIDUAL, GPT_TIMER_CONCATINATION) "
/*----*/		
#endif			
/*----*/

					gl_u32_is_initialized = TRUE;
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
*											02- GPT_vidStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT Timer counter
 * @in[1] 			: void
 * @return    : uint8_  [error status if Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_vidStart(void)
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (gl_u32_is_initialized == TRUE)
	{
/*----*/
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/	
			/*						Start Timer Counter			 */
			/*-------------------------------------------------------------*/
				SET_BIT(GPTMCTL_REG(gl_en_channel_id) , TAEN_IDX);
	
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B Start Counter will be implemented*/
/*----*/	
#endif
/*----*/		

/*----*/
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Start Timer Counter			 */
			/*-------------------------------------------------------------*/
				SET_BIT(GPTMCTL_REG(gl_en_channel_id) , TAEN_IDX);	
/*----*/
#endif
/*----*/
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	return loc_u8_err_state;
}

/*****************************************************************************************************************
*											03- GPT_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_vidStop(void)
{
/*----*/
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/	
			/*						Stop Timer Counter			 */
			/*-------------------------------------------------------------*/
					CLR_BIT(GPTMCTL_REG(gl_en_channel_id) , TAEN_IDX);	
	
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B Stop Counter will be implemented*/
/*----*/	
#endif
/*----*/		

/*----*/
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Stop Timer Counter			 */
			/*-------------------------------------------------------------*/
					CLR_BIT(GPTMCTL_REG(gl_en_channel_id) , TAEN_IDX);	
/*----*/
#endif
/*----*/
}


/*****************************************************************************************************************
*											05- GPT_vidIRQEnable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT enable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 	GPT_vidIRQEnable(void)
{
/*----*/
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/
	
			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMIMR_REG(gl_en_channel_id), TATOIM_IDX);
	
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B IRQ will be implemented*/
/*----*/	
#endif
/*----*/		

/*----*/
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMIMR_REG(gl_en_channel_id), TATOIM_IDX);	
/*----*/
#endif
/*----*/
return;
}

/*****************************************************************************************************************
*											06- GPT_vidIRQDisable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT disable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 	GPT_vidIRQDisable(void)
{
/*----*/
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/
	
			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMICR_REG(gl_en_channel_id), TATOCINT_IDX);
	
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B IRQ will be implemented*/
/*----*/
#endif
/*----*/	

/*----*/	
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Disable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMICR_REG(gl_en_channel_id), TATOCINT_IDX);	
				
/*----*/
#endif
/*----*/
	return;
}

/*****************************************************************************************************************
*											07- GPT_u8GetCurrentVal()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get GPT current value
 * @in[1] 		: p_u8_int_status
								- Address of Variable which GPT current value to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_u8GetCurrentVal(uint64_* p_u64_int_cur_val )
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (gl_u32_is_initialized == TRUE && p_u64_int_cur_val != NULL)
	{
/*----*/
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/
			*p_u64_int_cur_val = GPTMTAV_REG(gl_en_channel_id);
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B Get current val will be implemented*/
/*----*/
#endif
/*----*/	

/*----*/	
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
		uint32_ loc_u32_GPTMTBV_REG_val = GPTMTBV_REG(gl_en_channel_id);
					*p_u64_int_cur_val = ( ((uint64_)loc_u32_GPTMTBV_REG_val << 32U) | (GPTMTAV_REG(gl_en_channel_id)) );
/*----*/
#endif
/*----*/	
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	return loc_u8_err_state;	
}



/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*												Local APIs Implementation
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
static void set_tick_time(en_gpt_ch_id_t copy_en_gpt_ch_id, uint32_ copy_u32_time)
{
/*----*/
#if GPT_TIMER_CONC_SELECTION == GPT_TIMER_INDVIDUAL
/*----*/
	if (gl_en_time_init == GPT_TIME_US)
	{
		gl_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock/1000000U ) );
		gl_u32_time_out = (uint32_)gl_u64_gpt_ticks;
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/	
		GPTMTAILR_REG(copy_en_gpt_ch_id) = gl_u32_time_out;
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
#endif
/*----*/		
	}
	else if (gl_en_time_init == GPT_TIME_MS)
	{
		gl_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock/1000U ) );
		gl_u32_time_out = (uint32_)gl_u64_gpt_ticks;
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/
		GPTMTAILR_REG(copy_en_gpt_ch_id) = gl_u32_time_out;
/*----*/		
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
		/*todo: GPT_TIMER_B will be implemented*/
/*----*/
#endif	
/*----*/
	}
	else if (gl_en_time_init == GPT_TIME_S)
	{
		gl_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock ) );
		gl_u32_time_out = (uint32_)gl_u64_gpt_ticks;	
/*----*/		
#if GPT_TIMER_SELECTION == GPT_TIMER_A
/*----*/
		GPTMTAILR_REG(copy_en_gpt_ch_id) = gl_u32_time_out;
/*----*/
#elif GPT_TIMER_SELECTION == GPT_TIMER_B
/*----*/
		/*todo: GPT_TIMER_B will be implemented*/	
/*----*/	
#endif
/*----*/		
	}
	else 
	{
		/* do nothing */
	}
/*----*/	
#elif GPT_TIMER_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
	if (gl_en_time_init == GPT_TIME_US)
	{
		gl_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock/1000000U ) );			
		GPTMTAILR_REG(copy_en_gpt_ch_id) = (uint32_)gl_u64_gpt_ticks;
		
		if (gl_en_channel_id > GPT_CHANNEL_5 && gl_en_channel_id < GPT_CHANNEL_INVALID)
		{
			GPTMTBILR_REG(copy_en_gpt_ch_id) = (gl_u64_gpt_ticks >> 32U);
		}
		else
		{
			/* do nothing */
		}
	}
	else if (gl_en_time_init == GPT_TIME_MS)
	{
		gl_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock/1000U ) );
		GPTMTAILR_REG(copy_en_gpt_ch_id) = (uint32_)gl_u64_gpt_ticks;
		if (gl_en_channel_id > GPT_CHANNEL_5 && gl_en_channel_id < GPT_CHANNEL_INVALID)
		{
			GPTMTBILR_REG(copy_en_gpt_ch_id) = (gl_u64_gpt_ticks >> 32U);
		}
		else
		{
			/* do nothing */
		}
	}
	else if (gl_en_time_init == GPT_TIME_S)
	{
		gl_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock ) );
		GPTMTAILR_REG(copy_en_gpt_ch_id) = (uint32_)gl_u64_gpt_ticks;
		if (gl_en_channel_id > GPT_CHANNEL_5 && gl_en_channel_id < GPT_CHANNEL_INVALID)
		{
			GPTMTBILR_REG(copy_en_gpt_ch_id) = (gl_u64_gpt_ticks >> 32U);
		}
		else
		{
			/* do nothing */
		}		
	}
	else 
	{
		/* do nothing */
	}
/*----*/
#endif
/*----*/
}




/********************************************************************************************************************
*												IRQ Handler
********************************************************************************************************************/


void TIMER0A_Handler(void)
{
	if (gl_pf_gpt_ch0_cbk != NULL)
	{
		gl_pf_gpt_ch0_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void TIMER1A_Handler(void)
{
	if (gl_pf_gpt_ch1_cbk != NULL)
	{
		gl_pf_gpt_ch1_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}


void TIMER2A_Handler(void)
{
	if (gl_pf_gpt_ch2_cbk != NULL)
	{
		gl_pf_gpt_ch2_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}


void TIMER3A_Handler(void)
{
	if (gl_pf_gpt_ch3_cbk != NULL)
	{
		gl_pf_gpt_ch3_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void TIMER4A_Handler(void)
{
	if (gl_pf_gpt_ch4_cbk != NULL)
	{
		gl_pf_gpt_ch4_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void TIMER5A_Handler(void)
{
	if (gl_pf_gpt_ch5_cbk != NULL)
	{
		gl_pf_gpt_ch5_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}
