
 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 25 - 6 - 2023
 *  Description 			: timerM_Interface.h --> APIs Prototypes and Configurations
 *  Module Features		:
 *  											01- TIMM_u8Init()
 *  											02- TIMM_u8Start()
													03-	TIMM_vidStop()
													04-	TIMM_vidSynchDelay_ms()
													05-	TIMM_vidSynchDelay_us()
													06-	TIMM_vidSynchDelay_s()
 *****************************************************************************/


/*********************************************************************************************************
 *  									Includes
 ********************************************************************************************************/
#include "timerM_Interface.h"

 
/********************************************************************************************************************
 *  										APIs ProtoType
*******************************************************************************************************************/
/*****************************************************************************************************************
*											01- TIMM_u8Init()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: GPT Timer Intialization
 * @in[1] 		: Address of struct Instance
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ TIMM_u8Init(st_gpt_timer_cfg_t* st_gpt_timer_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state &= GPT_u8Init(st_gpt_timer_cfg);
	
	return loc_u8_err_state;
}

/*****************************************************************************************************************
*											02- TIMM_u8Start()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT Timer counter
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ TIMM_u8Start(void)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state &= GPT_u8Start();
	
	return loc_u8_err_state;	
}

/*****************************************************************************************************************
*											03- TIMM_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void TIMM_vidStop(void)
{
	GPT_vidStop();	
}

/*****************************************************************************************************************
*											04- TIMM_vidSynchDelay_ms()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Delsy in milli second
 * @in[1] 		: a_en_gpt_ch_id
 *								- {GPT_CHANNEL_0 ~ GPT_CHANNEL_5} - {GPT_WIDE_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5}
 * @in[1] 		: a_u32_time_ms
 *								- Set time in milli second								
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ TIMM_vidSynchDelay_ms(en_gpt_ch_id_t a_en_gpt_ch_id, uint32_ a_u32_time_ms)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state &= GPT_u8Delay_ms(a_en_gpt_ch_id, a_u32_time_ms);
	
	return loc_u8_err_state;	
}

/*****************************************************************************************************************
*											05- TIMM_vidSynchDelay_us()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Delsy in micro second
 * @in[1] 		: a_en_gpt_ch_id
 *								- {GPT_CHANNEL_0 ~ GPT_CHANNEL_5} - {GPT_WIDE_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5}
 * @in[1] 		: a_u32_time_us
 *								- Set time in micro second								
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ TIMM_vidSynchDelay_us(en_gpt_ch_id_t a_en_gpt_ch_id, uint32_ a_u32_time_us)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state &= GPT_u8Delay_us(a_en_gpt_ch_id, a_u32_time_us);
	
	return loc_u8_err_state;	
}

/*****************************************************************************************************************
*											06- TIMM_vidSynchDelay_s()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Set Delsy in second
 * @in[1] 		: a_en_gpt_ch_id
 *								- {GPT_CHANNEL_0 ~ GPT_CHANNEL_5} - {GPT_WIDE_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5}
 * @in[1] 		: a_u32_time_s
 *								- Set time in second								
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ TIMM_vidSynchDelay_s(en_gpt_ch_id_t a_en_gpt_ch_id, uint32_ a_u32_time_s)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state &= GPT_u8Delay_s(a_en_gpt_ch_id, a_u32_time_s);
	
	return loc_u8_err_state;	
}



