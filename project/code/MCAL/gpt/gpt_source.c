 /****************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 13 - 6 - 2023
 *  Description 			: gpt_Interface.h --> APIs Prototypes and Configurations
 *  Module Features		:
 *  											01- GPT_u8Init()
 *  											02- GPT_vidStart()
													03-	GPT_vidStop()
													04-	GPT_vidIRQEnable()
													05-	GPT_vidIRQDisable()
													06-	GPT_u8GetCurrentVal()
													07- GPT_u8DutyCycle()
													08- GPT_u8Delay_ms()
													09- GPT_u8Delay_us()
													10= GPT_u8Delay_s()
													11- GPT_u8PWMInit()
													12- GPT_u8GeneratePWM()
													13- GPT_u8PWMStart()
													14- GPT_u8PWMStop()
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
#include "bit_math.h"
/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*																Peripheral Files
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
#include "gpt_Private.h"
#include "gpt_Interface.h"
#include "gpt_Config.h"

/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*																		MACROS
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
#define GPT_WIDE_CHANNEL_ID_OFFSET			6
#define _16_BIT_MAX_LENGTH							0xFFFF
#define _32_BIT_MAX_LENGTH							0xFFFFFFFF
#define MAX_GPT_CHANNELS								12U
/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*															Global Static Variables
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
extern uint32_t 				SystemCoreClock;
static en_gpt_time_x_t	gs_en_time_init 							= GPT_TIME_INVALID;
static en_gpt_ch_id_t		gs_en_channel_id							= GPT_CHANNEL_INVALID; 
static en_gpt_ch_id_t		gs_en_pwm_channel_id					= GPT_CHANNEL_INVALID; 
static boolean					gs_bool_is_PR_used						= FALSE;
static uint32_ 					gs_u32_is_initialized 				= FALSE;
static boolean					gs_bool_is_pwm_initialized		= FALSE;
static uint64_ 					gs_u64_gpt_ticks;
static uint64_ 					gs_u64_pwm_total_ticks;
static uint32_					gs_u32_gpt_time;	
static uint32_					gs_u32_duty_cycle;

static ptr_func_t 			gs_pf_gpt_ch0_cbk 		= NULL;
static ptr_func_t 			gs_pf_gpt_ch1_cbk 		= NULL;
static ptr_func_t 			gs_pf_gpt_ch2_cbk 		= NULL;
static ptr_func_t 			gs_pf_gpt_ch3_cbk 		= NULL;
static ptr_func_t 			gs_pf_gpt_ch4_cbk 		= NULL;
static ptr_func_t 			gs_pf_gpt_ch5_cbk 		= NULL;

/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*												Local APIs Prototype
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
static void set_tick_time(uint32_ copy_u32_time);
static void set_pwm_tick_time(uint32_ copy_u32_time_ms);
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
 * @func  		: GPT_u8InitTimer Intialization
 * @in[1] 		: Address of struct Instance
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_u8Init(st_gpt_timer_cfg_t* st_gpt_timer_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	uint8_ loc_u8_channel_id;
	
	if (st_gpt_timer_cfg != NULL)
	{
		if (	st_gpt_timer_cfg->en_gpt_ch_id 			< 	GPT_CHANNEL_INVALID		&&
					st_gpt_timer_cfg->en_gpt_mode				< 	GPT_CH_MODE_INVALID		&&
					st_gpt_timer_cfg->en_gpt_irq				< 	GPT_IRQ_INVALID				&&
					st_gpt_timer_cfg->en_gpt_time_x			< 	GPT_TIME_INVALID			&&
					st_gpt_timer_cfg->en_gpt_stall			< 	GPT_STALL_INVALID			&&
					st_gpt_timer_cfg->u32_set_time			!= 	ZERO)
		{
			loc_u8_channel_id = st_gpt_timer_cfg->en_gpt_ch_id;
			gs_en_channel_id = st_gpt_timer_cfg->en_gpt_ch_id;
			
			
			/*						Enable Timer System Clock										*/
			/*-------------------------------------------------------------*/			
			if ( st_gpt_timer_cfg->en_gpt_ch_id > GPT_CHANNEL_5 && st_gpt_timer_cfg->en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				SET_BIT(RCGCWTIMER_REG, (loc_u8_channel_id - GPT_WIDE_CHANNEL_ID_OFFSET));
			}
			else 
			{
				SET_BIT(RCGCTIMER_REG, loc_u8_channel_id);
			}
				
			
/*----*/
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
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
				gs_en_time_init = GPT_TIME_US;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_MS)
			{
				gs_en_time_init = GPT_TIME_MS;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_S)
			{
				gs_en_time_init = GPT_TIME_S;
			}
			else 
			{
				/* do nothing */
			}
			set_tick_time(st_gpt_timer_cfg->u32_set_time);
			
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
#elif	GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/				
			/*todo: GPT_TIMER_B will be implemented*/
			
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
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
				//SET_BIT(GPTMCTL_REG(st_gpt_timer_cfg->en_gpt_ch_id ) , TASTALL_IDX);
				GPTMCTL_REG(loc_u8_channel_id ) |= ((1U) << TASTALL_IDX);
			}
			else 
			{
				/* do nothing */
			}
			
			/*						Choose Concatination Mode										*/
			/*-------------------------------------------------------------*/			
			GPTMCFG_REG(loc_u8_channel_id) =  0x00000000;
			
			/*						GPT mode Selection (one shot / periodic)				 */
			/*-------------------------------------------------------------*/					
			if (st_gpt_timer_cfg->en_gpt_mode == GPT_CH_MODE_ONE_SHOT)
			{
				GPTMTAMR_REG(loc_u8_channel_id) |= 0x1; 
			}
			else if(st_gpt_timer_cfg->en_gpt_mode == GPT_CH_MODE_PERIODIC)
			{
				GPTMTAMR_REG(loc_u8_channel_id) |= 0x2; 
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
			SET_BIT(GPTMTAMR_REG(st_gpt_timer_cfg->en_gpt_ch_id),TAILD_IDX);
/*----*/		
#elif GPT_TIMER_COUNT_SELECTION == GPT_COUNT_UP
/*----*/		
			SET_BIT(GPTMTAMR_REG(loc_u8_channel_id), TACDIR_IDX  );
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
				gs_en_time_init = GPT_TIME_US;
				gs_u32_gpt_time = st_gpt_timer_cfg->u32_set_time;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_MS)
			{
				gs_en_time_init = GPT_TIME_MS;
				gs_u32_gpt_time = st_gpt_timer_cfg->u32_set_time;
			}
			else if (st_gpt_timer_cfg->en_gpt_time_x == GPT_TIME_S)
			{
				gs_en_time_init = GPT_TIME_S;
				gs_u32_gpt_time = st_gpt_timer_cfg->u32_set_time;
			}
			else 
			{
				/* do nothing */
			}
			set_tick_time(st_gpt_timer_cfg->u32_set_time);
			
			/*						Set timer IRQ				 */
			/*-------------------------------------------------------------*/		
			if(st_gpt_timer_cfg->en_gpt_irq == GPT_IRQ_ENABLE)
			{
			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMIMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TATOIM_IDX);
				
			/*						Enable NVIC Timer Interrupt			 */
			/*-------------------------------------------------------------*/				
				if ((gs_en_channel_id == GPT_WIDE_CHANNEL_0) 		|| (gs_en_channel_id == GPT_CHANNEL_0) )
					NVIC_EnableIRQ(TIMER0A_IRQn);
				else if(gs_en_channel_id == GPT_WIDE_CHANNEL_1 	|| (gs_en_channel_id == GPT_CHANNEL_1) )
					NVIC_EnableIRQ(TIMER1A_IRQn);
				else if(gs_en_channel_id == GPT_WIDE_CHANNEL_2 	|| (gs_en_channel_id == GPT_CHANNEL_2) )
					NVIC_EnableIRQ(TIMER2A_IRQn);
				else if(gs_en_channel_id == GPT_WIDE_CHANNEL_3 	|| (gs_en_channel_id == GPT_CHANNEL_3) )
					NVIC_EnableIRQ(TIMER3A_IRQn);
				else if(gs_en_channel_id == GPT_WIDE_CHANNEL_4 	|| (gs_en_channel_id == GPT_CHANNEL_4) )
					NVIC_EnableIRQ(TIMER4A_IRQn);
				else if(gs_en_channel_id == GPT_WIDE_CHANNEL_5 	|| (gs_en_channel_id == GPT_CHANNEL_5) )
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
				CLR_BIT( GPTMIMR_REG(st_gpt_timer_cfg->en_gpt_ch_id), TATOIM_IDX);
			}
			else 
			{
				/* do nothing */
			}
			
			/*						Set Call Back Function			 */
			/*-------------------------------------------------------------*/
			if (st_gpt_timer_cfg->ptr_func != 	NULL	)
			{
					if (	(gs_en_channel_id == GPT_WIDE_CHANNEL_0) 		|| (gs_en_channel_id == GPT_CHANNEL_0) )
						gs_pf_gpt_ch0_cbk = st_gpt_timer_cfg->ptr_func;
					else if((gs_en_channel_id == GPT_WIDE_CHANNEL_1) 	|| (gs_en_channel_id == GPT_CHANNEL_1) )
						gs_pf_gpt_ch1_cbk = st_gpt_timer_cfg->ptr_func;
					else if((gs_en_channel_id == GPT_WIDE_CHANNEL_2) 	|| (gs_en_channel_id == GPT_CHANNEL_2) )
						gs_pf_gpt_ch2_cbk = st_gpt_timer_cfg->ptr_func;
					else if((gs_en_channel_id == GPT_WIDE_CHANNEL_3) 	|| (gs_en_channel_id == GPT_CHANNEL_3) )
						gs_pf_gpt_ch3_cbk = st_gpt_timer_cfg->ptr_func;
					else if((gs_en_channel_id == GPT_WIDE_CHANNEL_4) 	|| (gs_en_channel_id == GPT_CHANNEL_4) )
						gs_pf_gpt_ch4_cbk = st_gpt_timer_cfg->ptr_func;
					else if((gs_en_channel_id == GPT_WIDE_CHANNEL_5) 	|| (gs_en_channel_id == GPT_CHANNEL_5) )
						gs_pf_gpt_ch5_cbk = st_gpt_timer_cfg->ptr_func;
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
#else
/*----*/
#error "Invalid Timer please select either (GPT_TIMER_INDVIDUALI_TIMER_A, GPT_TIMER_INDVIDUALI_TIMER_B, GPT_TIMER_CONCATINATION) "
/*----*/		
#endif			
/*----*/

					gs_u32_is_initialized = TRUE;
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
uint8_ GPT_u8Start(void)
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (gs_u32_is_initialized == TRUE )
	{

/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/	
			/*						Start Timer Counter			 */
			/*-------------------------------------------------------------*/
				SET_BIT(GPTMCTL_REG(gs_en_channel_id) , TAEN_IDX);
	
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B Start Counter will be implemented*/
		

/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Start Timer Counter			 */
			/*-------------------------------------------------------------*/
				SET_BIT(GPTMCTL_REG(gs_en_channel_id) , TAEN_IDX);	
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
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/	
			/*						Stop Timer Counter			 */
			/*-------------------------------------------------------------*/
					CLR_BIT(GPTMCTL_REG(gs_en_channel_id) , TAEN_IDX);	
	
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B Stop Counter will be implemented*/
	
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Stop Timer Counter			 */
			/*-------------------------------------------------------------*/
					CLR_BIT(GPTMCTL_REG(gs_en_channel_id) , TAEN_IDX);	
/*----*/
#endif
/*----*/
}


/*****************************************************************************************************************
*											04- GPT_vidIRQEnable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT enable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 	GPT_vidIRQEnable(void)
{

/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/
	
			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMIMR_REG(gs_en_channel_id), TATOIM_IDX);
	
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B IRQ will be implemented*/
		

/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMIMR_REG(gs_en_channel_id), TATOIM_IDX);	
/*----*/
#endif
/*----*/
return;
}

/*****************************************************************************************************************
*											05- GPT_vidIRQDisable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT disable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 	GPT_vidIRQDisable(void)
{

/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/
	
			/*						Enable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				SET_BIT( GPTMICR_REG(gs_en_channel_id), TATOCINT_IDX);
	
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B IRQ will be implemented*/


/*----*/	
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/

			/*						Disable Timer Peripheral Interrupt			 */
			/*-------------------------------------------------------------*/
				CLR_BIT( GPTMIMR_REG(gs_en_channel_id), TATOIM_IDX);	
				
/*----*/
#endif
/*----*/
	return;
}

/*****************************************************************************************************************
*											06- GPT_u8GetCurrentVal()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get GPT current value
 * @in[1] 		: p_u8_int_status
								- Address of Variable which GPT current value to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_u8GetCurrentVal(uint64_* p_u64_int_cur_val )
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (gs_u32_is_initialized == TRUE && p_u64_int_cur_val != NULL)
	{

/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/
			*p_u64_int_cur_val = GPTMTAV_REG(gs_en_channel_id);
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
				/*todo: GPT_TIMER_B Get current val will be implemented*/
	

/*----*/	
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
		uint32_ loc_u32_GPTMTBV_REG_val = GPTMTBV_REG(gs_en_channel_id);
					*p_u64_int_cur_val = ( ((uint64_)loc_u32_GPTMTBV_REG_val << 32U) | (GPTMTAV_REG(gs_en_channel_id)) );
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
*											07- GPT_u8DutyCycle()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Duty Cycle
 * @in[1] 		: u32_a_duty_cycle
								- Duty Cycle { 0 ~ 100 }
 * @return    : void
 ******************************************************************************************************************/
void GPT_u8DutyCycle(uint32_ u32_a_duty_cycle)
{
	uint32_ loc_u32_match;
	gs_u32_duty_cycle = 100U - u32_a_duty_cycle;
	//gs_u8_invert_duty_cycle = u8_a_duty_cycle;
	loc_u32_match = gs_u32_gpt_time * (gs_u32_duty_cycle/ 100.0);

		set_tick_time(loc_u32_match);	
	return;
}

/*****************************************************************************************************************
*											08- GPT_u8Delay_ms()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Delsy in milli second
 * @in[1] 		: a_en_gpt_ch_id
 *								- {GPT_CHANNEL_0 ~ GPT_CHANNEL_5} - {GPT_WIDE_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5}
 * @in[1] 		: a_u32_time_ms
 *								- Set time in milli second								
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8Delay_ms( en_gpt_ch_id_t a_en_gpt_ch_id, uint32_ a_u32_time_ms)
{
	uint8_ loc_u8_err_state = SUCCESS;
	static boolean Ls_bool_is_first_time = TRUE;
	static en_gpt_ch_id_t Ls_en_prev_channel = GPT_CHANNEL_INVALID;
	uint64_ loc_u64_gpt_ticks;
	if (a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
	{	
/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/	
		
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
		
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
	
		
		if(Ls_bool_is_first_time == TRUE || Ls_en_prev_channel != a_en_gpt_ch_id)
		{
						/*						Enable Timer System Clock										*/
			/*-------------------------------------------------------------*/			
			if ( a_en_gpt_ch_id> GPT_CHANNEL_5 && a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				SET_BIT(RCGCWTIMER_REG, (a_en_gpt_ch_id - GPT_WIDE_CHANNEL_ID_OFFSET));
			}
			else 
			{
				SET_BIT(RCGCTIMER_REG, a_en_gpt_ch_id);
			}
			
			/*						Ensure the timer is disabled										*/
			/*-------------------------------------------------------------*/
			CLR_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TAEN_IDX);
			
						/* STALL enable during debugging */
			SET_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TASTALL_IDX);
			
						/* counter count down */
			CLR_BIT(GPTMTAMR_REG(a_en_gpt_ch_id), TACDIR_IDX  );
			SET_BIT(GPTMTAMR_REG(a_en_gpt_ch_id),TAILD_IDX);
			
			/* IRQ Disable */
			CLR_BIT( GPTMIMR_REG(a_en_gpt_ch_id), TATOIM_IDX);			
			
			Ls_bool_is_first_time = FALSE;
		}

			
			loc_u64_gpt_ticks = (uint64_) ( (a_u32_time_ms)* (SystemCoreClock/1000U ) );
			GPTMTAILR_REG(a_en_gpt_ch_id) = (uint32_)loc_u64_gpt_ticks;
			
			if (a_en_gpt_ch_id > GPT_CHANNEL_5 && a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				GPTMTBILR_REG(a_en_gpt_ch_id) = (gs_u64_gpt_ticks >> 32U);
			}
			else
			{
				/* do nothing */
			}	

			/*						Timer is enabled									*/
			/*-------------------------------------------------------------*/
			if(Ls_bool_is_first_time == TRUE || Ls_en_prev_channel != a_en_gpt_ch_id)
							SET_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TAEN_IDX);		
			
			
			while ( GET_BIT(GPTMRIS_REG(a_en_gpt_ch_id), TATORIS_IDX)  == 0);
			SET_BIT( GPTMICR_REG(a_en_gpt_ch_id) ,TATOCINT_IDX);
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
*											09- GPT_u8Delay_us()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Delsy in micro second
 * @in[1] 		: a_en_gpt_ch_id
 *								- {GPT_CHANNEL_0 ~ GPT_CHANNEL_5} - {GPT_WIDE_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5}
 * @in[1] 		: a_u32_time_us
 *								- Set time in micro second								
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8Delay_us( en_gpt_ch_id_t a_en_gpt_ch_id, uint32_ a_u32_time_us)
{
	uint8_ loc_u8_err_state = SUCCESS;
	static boolean Ls_bool_is_first_time = TRUE;
	static en_gpt_ch_id_t Ls_en_prev_channel = GPT_CHANNEL_INVALID;
	uint64_ loc_u64_gpt_ticks;
	if (a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
	{	
/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/	
		
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
		
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
	
		
		if(Ls_bool_is_first_time == TRUE || Ls_en_prev_channel != a_en_gpt_ch_id)
		{
						/*						Enable Timer System Clock										*/
			/*-------------------------------------------------------------*/			
			if ( a_en_gpt_ch_id> GPT_CHANNEL_5 && a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				SET_BIT(RCGCWTIMER_REG, (a_en_gpt_ch_id - GPT_WIDE_CHANNEL_ID_OFFSET));
			}
			else 
			{
				SET_BIT(RCGCTIMER_REG, a_en_gpt_ch_id);
			}
			
			/*						Ensure the timer is disabled										*/
			/*-------------------------------------------------------------*/
			CLR_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TAEN_IDX);
			
						/* STALL enable during debugging */
			SET_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TASTALL_IDX);
			
						/* counter count down */
			CLR_BIT(GPTMTAMR_REG(a_en_gpt_ch_id), TACDIR_IDX  );
			SET_BIT(GPTMTAMR_REG(a_en_gpt_ch_id),TAILD_IDX);
			
			/* IRQ Disable */
			CLR_BIT( GPTMIMR_REG(a_en_gpt_ch_id), TATOIM_IDX);			
			
			Ls_bool_is_first_time = FALSE;
		}

			
			loc_u64_gpt_ticks = (uint64_) ( (a_u32_time_us)* (SystemCoreClock/1000000U ) );
			GPTMTAILR_REG(a_en_gpt_ch_id) = (uint32_)loc_u64_gpt_ticks;
			
			if (a_en_gpt_ch_id > GPT_CHANNEL_5 && a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				GPTMTBILR_REG(a_en_gpt_ch_id) = (gs_u64_gpt_ticks >> 32U);
			}
			else
			{
				/* do nothing */
			}	

			/*						Timer is enabled									*/
			/*-------------------------------------------------------------*/
			if(Ls_bool_is_first_time == TRUE || Ls_en_prev_channel != a_en_gpt_ch_id)
							SET_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TAEN_IDX);		
			
			
			while ( GET_BIT(GPTMRIS_REG(a_en_gpt_ch_id), TATORIS_IDX)  == 0);
			SET_BIT( GPTMICR_REG(a_en_gpt_ch_id) ,TATOCINT_IDX);
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
*											10- GPT_u8Delay_s()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Delsy in second
 * @in[1] 		: a_en_gpt_ch_id
 *								- {GPT_CHANNEL_0 ~ GPT_CHANNEL_5} - {GPT_WIDE_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5}
 * @in[1] 		: a_u32_time_s
 *								- Set time in second								
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8Delay_s( en_gpt_ch_id_t a_en_gpt_ch_id, uint32_ a_u32_time_s)
{
	uint8_ loc_u8_err_state = SUCCESS;
	static boolean Ls_bool_is_first_time = TRUE;
	static en_gpt_ch_id_t Ls_en_prev_channel = GPT_CHANNEL_INVALID;
	uint64_ loc_u64_gpt_ticks;
	if (a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
	{	
/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/	
		
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
		
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
	
		
		if(Ls_bool_is_first_time == TRUE || Ls_en_prev_channel != a_en_gpt_ch_id)
		{
						/*						Enable Timer System Clock										*/
			/*-------------------------------------------------------------*/			
			if ( a_en_gpt_ch_id> GPT_CHANNEL_5 && a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				SET_BIT(RCGCWTIMER_REG, (a_en_gpt_ch_id - GPT_WIDE_CHANNEL_ID_OFFSET));
			}
			else 
			{
				SET_BIT(RCGCTIMER_REG, a_en_gpt_ch_id);
			}
			
			/*						Ensure the timer is disabled										*/
			/*-------------------------------------------------------------*/
			CLR_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TAEN_IDX);
			
						/* STALL enable during debugging */
			SET_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TASTALL_IDX);
			
						/* counter count down */
			CLR_BIT(GPTMTAMR_REG(a_en_gpt_ch_id), TACDIR_IDX  );
			SET_BIT(GPTMTAMR_REG(a_en_gpt_ch_id),TAILD_IDX);
			
			/* IRQ Disable */
			CLR_BIT( GPTMIMR_REG(a_en_gpt_ch_id), TATOIM_IDX);			
			
			Ls_bool_is_first_time = FALSE;
		}

			
			loc_u64_gpt_ticks = (uint64_) ( (a_u32_time_s)* (SystemCoreClock) );
			GPTMTAILR_REG(a_en_gpt_ch_id) = (uint32_)loc_u64_gpt_ticks;
			
			if (a_en_gpt_ch_id > GPT_CHANNEL_5 && a_en_gpt_ch_id < GPT_CHANNEL_INVALID)
			{
				GPTMTBILR_REG(a_en_gpt_ch_id) = (gs_u64_gpt_ticks >> 32U);
			}
			else
			{
				/* do nothing */
			}	

			/*						Timer is enabled									*/
			/*-------------------------------------------------------------*/
			if(Ls_bool_is_first_time == TRUE || Ls_en_prev_channel != a_en_gpt_ch_id)
							SET_BIT(GPTMCTL_REG(a_en_gpt_ch_id ) , TAEN_IDX);		
			
			
			while ( GET_BIT(GPTMRIS_REG(a_en_gpt_ch_id), TATORIS_IDX)  == 0);
			SET_BIT( GPTMICR_REG(a_en_gpt_ch_id) ,TATOCINT_IDX);
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
*											11- GPT_u8PWMInit()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get GPT current value
 * @in[1] 		: copy_en_gpt_ch_id
 *								- GPT_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5
 * @in[2] 		: copy_u32_period_time_ms
 *							- Interval periodic time in milli second 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8PWMInit(st_gpt_pwm_cfg_t* p_st_gpt_pwm_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	if (p_st_gpt_pwm_cfg == NULL)
	{
		loc_u8_err_state = FAILED;
	}
	else
	{
		if (p_st_gpt_pwm_cfg->en_gpt_ch_id 			< GPT_CHANNEL_INVALID 		&& 
				p_st_gpt_pwm_cfg->u32_set_time_ms 	!= ZERO										&&
				p_st_gpt_pwm_cfg->en_gpt_stall			<	GPT_STALL_INVALID				&&
				p_st_gpt_pwm_cfg->en_gpt_irq				< GPT_IRQ_INVALID )
		{
				gs_en_pwm_channel_id = p_st_gpt_pwm_cfg->en_gpt_ch_id;

				/*						Enable Timer System Clock										*/
				/*-------------------------------------------------------------*/				
				if ( p_st_gpt_pwm_cfg->en_gpt_ch_id > GPT_CHANNEL_5 && p_st_gpt_pwm_cfg->en_gpt_ch_id < GPT_CHANNEL_INVALID)
				{
					SET_BIT(RCGCWTIMER_REG, (p_st_gpt_pwm_cfg->en_gpt_ch_id - GPT_WIDE_CHANNEL_ID_OFFSET));
				}
				else 
				{
					SET_BIT(RCGCTIMER_REG, p_st_gpt_pwm_cfg->en_gpt_ch_id);
				}		
				
	/*----*/		
	#if GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_A
	/*----*/
				
				/*						Ensure the timer is disabled										*/
				/*-------------------------------------------------------------*/
				CLR_BIT(GPTMCTL_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id ) , TAEN_IDX);	
						
			/*						Counting STOP/RUNNING during debugging					 */
			/*-------------------------------------------------------------*/		
			if (p_st_gpt_pwm_cfg->en_gpt_stall == GPT_STALL_DISABLE)
			{
				CLR_BIT(GPTMCTL_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id ) , TASTALL_IDX);
				
			}
			else if(p_st_gpt_pwm_cfg->en_gpt_stall == GPT_STALL_ENABLE)
			{
				SET_BIT(GPTMCTL_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) , TASTALL_IDX);
				//GPTMCTL_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id ) |= ((1U) << TASTALL_IDX);
			}
			else 
			{
				/* do nothing */
			}

				/*						Choose Indvidual Mode										*/
				/*-------------------------------------------------------------*/			
				GPTMCFG_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id ) = 0x4;
				
				/*						Timer Counting Down				 */
				/*-------------------------------------------------------------*/					
				CLR_BIT(GPTMTAMR_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) , TACDIR_IDX  );

				/*Periodic Timer mode, Edge-Count mode, PWM mode is enabled		 */
				/*-------------------------------------------------------------*/				
				GPTMTAMR_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) |= 0xA;
				
				/*				Selecting Non-Inverting Mode	 */
				/*-------------------------------------------------------------*/				
				CLR_BIT(GPTMCTL_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id),TAPWML_IDX);
				
				/*				GPTM Timer A Event Mode on Both Edges	 */
				/*-------------------------------------------------------------*/				
				//GPTMCTL_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) |= ( (0x3) << TAEVENT_IDX );
				
				
				/*				GPTM Timer A PWM Set Time Tick */
				/*-------------------------------------------------------------*/			
				set_pwm_tick_time(p_st_gpt_pwm_cfg->u32_set_time_ms);
				
				
				
			/*						Set timer IRQ				 */
			/*-------------------------------------------------------------*/		
			if(p_st_gpt_pwm_cfg->en_gpt_irq == GPT_IRQ_ENABLE)
			{
				/*				GPTM Timer A PWM Interrupt Enable	 */
				/*-------------------------------------------------------------*/			
				//SET_BIT(GPTMTAMR_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) ,TAPWMIE_IDX);
				SET_BIT(GPTMIMR_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) ,CAMIM_IDX);
				
				
				/*						Enable NVIC Timer Interrupt			 */
				/*-------------------------------------------------------------*/				
					if ((p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_0) 		|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_0) )
						NVIC_EnableIRQ(TIMER0A_IRQn);
					else if(p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_1 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_1) )
						NVIC_EnableIRQ(TIMER1A_IRQn);
					else if(p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_2 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_2) )
						NVIC_EnableIRQ(TIMER2A_IRQn);
					else if(p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_3 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_3) )
						NVIC_EnableIRQ(TIMER3A_IRQn);
					else if(p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_4 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_4) )
						NVIC_EnableIRQ(TIMER4A_IRQn);
					else if(p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_5 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_5) )
						NVIC_EnableIRQ(TIMER5A_IRQn);
					else
					{
						/* do nothing */
					}
					
				/*						Enable Global Interrupt			 */
				/*-------------------------------------------------------------*/
				__enable_irq();							
			}
			else if (p_st_gpt_pwm_cfg->en_gpt_irq == GPT_IRQ_DISABLE)
			{
				CLR_BIT(GPTMTAMR_REG(p_st_gpt_pwm_cfg->en_gpt_ch_id) ,TAPWMIE_IDX);
			}
			else 
			{
				/* do nothing */
			}				
				
				
			/*						Set Call Back Function			 */
			/*-------------------------------------------------------------*/
			if (p_st_gpt_pwm_cfg->ptr_func != NULL)
			{
					if (	(p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_0) 		|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_0) )
						gs_pf_gpt_ch0_cbk = p_st_gpt_pwm_cfg->ptr_func;
					else if((p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_1) 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_1) )
						gs_pf_gpt_ch1_cbk = p_st_gpt_pwm_cfg->ptr_func;
					else if((p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_2) 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_2) )
						gs_pf_gpt_ch2_cbk = p_st_gpt_pwm_cfg->ptr_func;
					else if((p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_3) 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_3) )
						gs_pf_gpt_ch3_cbk = p_st_gpt_pwm_cfg->ptr_func;
					else if((p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_4) 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_4) )
						gs_pf_gpt_ch4_cbk = p_st_gpt_pwm_cfg->ptr_func;
					else if((p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_WIDE_CHANNEL_5) 	|| (p_st_gpt_pwm_cfg->en_gpt_ch_id == GPT_CHANNEL_5) )
						gs_pf_gpt_ch5_cbk = p_st_gpt_pwm_cfg->ptr_func;
					else
					{
						/* do nothing */
					}					
			}
			else 
			{
				/* do nothing */
			}
					
				
				gs_bool_is_pwm_initialized = TRUE;

	/*----*/
	#elif GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_B
	/*----*/
					/*todo: GPT_TIMER_B Get current val will be implemented*/
	/*----*/
	#endif
	/*----*/	
		}
		else 
		{
			loc_u8_err_state = FAILED;
		}		
	}
	
	return loc_u8_err_state;		
}


/*****************************************************************************************************************
*											12- GPT_u8GeneratePWM()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Generate PWM signal
 * @in[1] 		: copy_en_gpt_ch_id
 *								- GPT_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5 
 * @in[2] 		: copy_u8_duty_cycle
								- Duty cycle ( 0 ~ 100 ) 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8GeneratePWM(uint8_ copy_u8_duty_cycle)
{
	uint8_ loc_u8_err_state = SUCCESS;
	uint64_ loc_u64_match;
	uint8_ loc_u8_duty_cycle = 100U - copy_u8_duty_cycle;
	if (gs_bool_is_pwm_initialized == TRUE && copy_u8_duty_cycle <= 100U && gs_en_pwm_channel_id < GPT_CHANNEL_INVALID)
	{
		
		loc_u64_match = gs_u64_pwm_total_ticks - (gs_u64_pwm_total_ticks * (loc_u8_duty_cycle / 100.0));
/*----*/		
#if  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_A
/*----*/
	
		if (gs_bool_is_PR_used == FALSE )
		{
			if(gs_en_pwm_channel_id > GPT_CHANNEL_5 && gs_en_pwm_channel_id < GPT_CHANNEL_INVALID )
			{
				GPTMTAMATCHR_REG(gs_en_pwm_channel_id) = (uint32_) loc_u64_match;
			}
			else 
			{
				GPTMTAMATCHR_REG(gs_en_pwm_channel_id) = (uint16_) loc_u64_match;
			}
		}
		else if (gs_bool_is_PR_used == TRUE)
		{
			if(gs_en_pwm_channel_id > GPT_CHANNEL_5 && gs_en_pwm_channel_id < GPT_CHANNEL_INVALID )
			{
				GPTMTAPMR_REG(gs_en_pwm_channel_id)  = (uint16_)  loc_u64_match ;
				GPTMTAMATCHR_REG(gs_en_pwm_channel_id) = (uint32_) (loc_u64_match >> 16U);
				
			}
			else 
			{
				GPTMTAPMR_REG(gs_en_pwm_channel_id)  		= (uint8_)  loc_u64_match ;
				GPTMTAMATCHR_REG(gs_en_pwm_channel_id) 	= (uint32_)(loc_u64_match >> 8U);
			}
		}
		else 
		{
			/* do nothing */
		}

		
/*----*/		
#elif  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_B
/*----*/
		
		
#endif			
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
	
		return loc_u8_err_state;
}

/*****************************************************************************************************************
*											13- GPT_u8PWMStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT PWM generation
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8PWMStart(void)
{
	uint8_ loc_u8_err_state = SUCCESS;
	if (gs_bool_is_pwm_initialized == TRUE )
	{	
/*----*/		
#if  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_A
/*----*/
	
			/*						Start Timer Counter			 */
			/*-------------------------------------------------------------*/
				SET_BIT(GPTMCTL_REG(gs_en_pwm_channel_id) , TAEN_IDX);	
		
/*----*/		
#elif  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_B
/*----*/	
#endif			
	}
	else 
	{
		loc_u8_err_state = FAILED;
	}
		return loc_u8_err_state;		
}


/*****************************************************************************************************************
*											14- GPT_u8PWMStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT PWM generation
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_u8PWMStop(void)
{
/*----*/		
#if  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_A
/*----*/
	
			/*						Stop Timer Counter			 */
			/*-------------------------------------------------------------*/
					CLR_BIT(GPTMCTL_REG(gs_en_pwm_channel_id) , TAEN_IDX);
		
/*----*/		
#elif  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_B
/*----*/	
#endif		
}

/********************************************************************************************************************
********************************************************************************************************************/
/********************************************************************************************************************
*												Local APIs Implementation
********************************************************************************************************************/
/********************************************************************************************************************
********************************************************************************************************************/
static void set_tick_time(uint32_ copy_u32_time)
{
	
	if (gs_en_time_init == GPT_TIME_US)
	{
		gs_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock/1000000U ) );

/*----*/		
#if GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/	
		GPTMTAILR_REG(copy_en_gpt_ch_id) = (uint32_)gs_u64_gpt_ticks;
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
		GPTMTBILR_REG(copy_en_gpt_ch_id) = (uint32_)gs_u64_gpt_ticks;
/*----*/
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
		GPTMTAILR_REG(gs_en_channel_id) = (uint32_)gs_u64_gpt_ticks;
		
		if (gs_en_channel_id > GPT_CHANNEL_5 && gs_en_channel_id < GPT_CHANNEL_INVALID)
		{
			GPTMTBILR_REG(gs_en_channel_id) = (gs_u64_gpt_ticks >> 32U);
		}
		else
		{
			/* do nothing */
		}		
/*----*/
#endif
/*----*/		
	}
	else if (gs_en_time_init == GPT_TIME_MS)
	{
		gs_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock/1000U ) );

/*----*/		
#if  GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/
		GPTMTAILR_REG(copy_en_gpt_ch_id) = (uint32_)gs_u64_gpt_ticks;
/*----*/		
#elif  GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
		GPTMTBILR_REG(copy_en_gpt_ch_id) = (uint32_)gs_u64_gpt_ticks;
		
/*----*/	
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
		GPTMTAILR_REG(gs_en_channel_id) &= 0x0;
		GPTMTAILR_REG(gs_en_channel_id) = (uint32_)gs_u64_gpt_ticks;
		
		if (gs_en_channel_id > GPT_CHANNEL_5 && gs_en_channel_id < GPT_CHANNEL_INVALID)
		{
			GPTMTBILR_REG(gs_en_channel_id) = (gs_u64_gpt_ticks >> 32U);
		}
		else
		{
			/* do nothing */
		}
		
/*----*/
#endif	
/*----*/
	}
	else if (gs_en_time_init == GPT_TIME_S)
	{
		gs_u64_gpt_ticks = (uint64_) ( (copy_u32_time)* (SystemCoreClock ) );
/*----*/		
#if  GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_A
/*----*/
		GPTMTAILR_REG(gs_en_channel_id) = (uint32_)gs_u64_gpt_ticks;
/*----*/
#elif  GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_INDVIDUAL_TIMER_B
/*----*/
		GPTMTBILR_REG(gs_en_channel_id) = (uint32_)gs_u64_gpt_ticks;
		
/*----*/		
#elif GPT_TIMER_INDV_CONC_SELECTION == GPT_TIMER_CONCATINATION
/*----*/
		GPTMTAILR_REG(gs_en_channel_id) = (uint32_)gs_u64_gpt_ticks;
		
		if (gs_en_channel_id > GPT_CHANNEL_5 && gs_en_channel_id < GPT_CHANNEL_INVALID)
		{
			GPTMTBILR_REG(gs_en_channel_id) = (gs_u64_gpt_ticks >> 32U);
		}
		else
		{
			/* do nothing */
		}
/*----*/	
#endif
/*----*/		
	}
	else 
	{
		/* do nothing */
	}
}





static void set_pwm_tick_time(uint32_ copy_u32_time_ms)
{
	
/*----*/		
#if  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_A
/*----*/
	
		gs_u64_pwm_total_ticks =  (uint64_)(copy_u32_time_ms)* (SystemCoreClock/1000U );

		if ( (gs_u64_pwm_total_ticks <= _16_BIT_MAX_LENGTH && gs_en_pwm_channel_id < GPT_WIDE_CHANNEL_0) || (gs_u64_pwm_total_ticks <= _32_BIT_MAX_LENGTH && gs_en_pwm_channel_id > GPT_CHANNEL_5) )
		{
			if(gs_en_pwm_channel_id > GPT_CHANNEL_5 && gs_en_pwm_channel_id < GPT_CHANNEL_INVALID )
			{
				GPTMTAILR_REG(gs_en_pwm_channel_id) = (uint32_)gs_u64_pwm_total_ticks;
			}
			else 
			{
				GPTMTAILR_REG(gs_en_pwm_channel_id) = (uint16_) gs_u64_gpt_ticks;
			}
		}
		else 
		{
			if(gs_en_pwm_channel_id > GPT_CHANNEL_5 && gs_en_pwm_channel_id < GPT_CHANNEL_INVALID )
			{
				GPTMTAPR_REG(gs_en_pwm_channel_id)  = (uint16_)  gs_u64_pwm_total_ticks ;
				GPTMTAILR_REG(gs_en_pwm_channel_id) = (uint32_) (gs_u64_pwm_total_ticks >> 16U);
				
			}
			else 
			{
				GPTMTAPR_REG(gs_en_pwm_channel_id)  = (uint8_)  gs_u64_pwm_total_ticks ;
				GPTMTAILR_REG(gs_en_pwm_channel_id) = (uint32_)(gs_u64_pwm_total_ticks >> 8U);
			}
			
			gs_bool_is_PR_used = TRUE;
		}
	
		
/*----*/		
#elif  GPT_PWM_TIMER_SELECTION == GPT_PWM_TIMER_B
/*----*/
		GPTMTBILR_REG(copy_en_gpt_ch_id) = (uint32_)gs_u64_gpt_ticks;
		
		
#endif	
}


/********************************************************************************************************************
*												IRQ Handler
********************************************************************************************************************/


void TIMER0A_Handler(void)
{
	static boolean loc_s_bool_duty_flag = FALSE;
	if (gs_pf_gpt_ch0_cbk != NULL)
	{
		SET_BIT( GPTMICR_REG(gs_en_channel_id), TATOCINT_IDX);
		//SET_BIT( GPTMICR_REG(gs_en_channel_id), CAMCINT_IDX);
			gs_pf_gpt_ch0_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void TIMER1A_Handler(void)
{
	if (gs_pf_gpt_ch1_cbk != NULL)
	{
		gs_pf_gpt_ch1_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}


void TIMER2A_Handler(void)
{
	if (gs_pf_gpt_ch2_cbk != NULL)
	{
		gs_pf_gpt_ch2_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}


void TIMER3A_Handler(void)
{
	if (gs_pf_gpt_ch3_cbk != NULL)
	{
		gs_pf_gpt_ch3_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void TIMER4A_Handler(void)
{
	if (gs_pf_gpt_ch4_cbk != NULL)
	{
		gs_pf_gpt_ch4_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}

void TIMER5A_Handler(void)
{
	if (gs_pf_gpt_ch5_cbk != NULL)
	{
		gs_pf_gpt_ch5_cbk();
	}
	else
	{
		/* do nothing */
	}
	
}
