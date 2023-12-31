
 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 13 - 6 - 2023
 *  Description 			: gpt_Interface.h --> APIs Prototypes and Configurations
 *  Module Features		:
 *  											01- GPT_MANAGER_u8Init()
 *  											02- GPT_MANAGER_vidStart()
													03-	GPT_MANAGER_vidStop()
													04-	GPT_MANAGER_vidIRQEnable()
													05-	GPT_MANAGER_vidIRQDisable()
													06-	GPT_MANAGER_u8GetCurrentVal()
													07- GPT_MANAGER_u8PWMInit()
													08- GPT_MANAGER_u8GeneratePWM()
													09- GPT_MANAGER_u8PWMStart()
													10- GPT_MANAGER_u8PWMStop()
 *****************************************************************************/

/*********************************************************************************************************
 *  										Header Guard Of File
 ********************************************************************************************************/
#ifndef GPT_MANAGER_INTERFACE_H_
#define GPT_MANAGER_INTERFACE_H_
/*********************************************************************************************************
 *  									Includes
 ********************************************************************************************************/
#include "gpt_Interface.h"

/********************************************************************************************************************
 *  										APIs ProtoType
*******************************************************************************************************************/

/*****************************************************************************************************************
*											01- GPT_u8Init()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: GPT_u8InitTimer Intialization
 * @in[1] 		: Address of struct Instance
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_MANAGER_u8Init(st_gpt_timer_cfg_t* st_gpt_timer_cfg);

/*****************************************************************************************************************
*											02- GPT_vidStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT Timer counter
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_MANAGER_u8Start(void);


/*****************************************************************************************************************
*											03- GPT_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_MANAGER_vidStop(void);


/*****************************************************************************************************************
*											04- GPT_vidIRQEnable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT enable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		GPT_MANAGER_vidIRQEnable(void);

/*****************************************************************************************************************
*											05- GPT_vidIRQDisable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT disable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		GPT_MANAGER_vidIRQDisable(void);

/*****************************************************************************************************************
*											06- GPT_u8GetCurrentVal()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get GPT current value
 * @in[1] 		: p_u8_int_status
								- Address of Variable which GPT current value to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_MANAGER_u8GetCurrentVal(uint64_* p_u64_int_cur_val );



void GPT_MANAGER_u8DutyCycle(uint32_ u32_a_duty_cycle);

/*****************************************************************************************************************
*											07- GPT_u8PWMInit()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Initialize PWM
 * @in[1] 		: copy_en_gpt_ch_id
 *								- GPT_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5
 * @in[2] 		: copy_u32_period_time_ms
 *							- Interval periodic time in milli second 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_MANAGER_u8PWMInit(st_gpt_pwm_cfg_t* p_st_gpt_pwm_cfg);


/*****************************************************************************************************************
*											08- GPT_u8GeneratePWM()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Generate PWM signal
 * @in[1] 		: copy_en_gpt_ch_id
 *								- GPT_CHANNEL_0 ~ GPT_WIDE_CHANNEL_5 
 * @in[2] 		: copy_u8_duty_cycle
								- Duty cycle ( 0 ~ 100 ) 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_MANAGER_u8GeneratePWM(uint8_ copy_u8_duty_cycle);


/*****************************************************************************************************************
*											09- GPT_u8PWMStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT PWM generation
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_MANAGER_u8PWMStart(void);


/*****************************************************************************************************************
*											10- GPT_u8PWMStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT PWM generation
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_MANAGER_u8PWMStop(void);

#endif /*GPT_MANAGER_INTERFACE_H_*/

