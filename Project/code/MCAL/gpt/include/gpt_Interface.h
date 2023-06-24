
 /**************************************************************
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
													07- GPT_u8PWMInit()
													08- GPT_u8GeneratePWM()
													09- GPT_u8PWMStart()
													10- GPT_u8PWMStop()
 *****************************************************************************/

/*********************************************************************************************************
 *  										Header Guard Of File
 ********************************************************************************************************/
#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_
/*********************************************************************************************************
 *  									Includes
 ********************************************************************************************************/
#include "LSTD_TYPES.h"

/*********************************************************************************************************
 *  									MACROS
 ********************************************************************************************************/

#define DUTY_CYCLE_INVALID				150

 /*									Timer Concatination / Indvidula Selection								
 ------------------------------------------------------------------*/
#define GPT_TIMER_INDVIDUAL_TIMER_A				0
#define GPT_TIMER_INDVIDUAL_TIMER_B				1
#define GPT_TIMER_CONCATINATION						2
#define GPT_TIMER_INDV_CONC_SELECTION			GPT_TIMER_CONCATINATION


 /*									Timer for PWM Selection							
 ------------------------------------------------------------------*/
#define GPT_PWM_TIMER_A				0
#define GPT_PWM_TIMER_B				1
#define GPT_PWM_TIMER_SELECTION			GPT_PWM_TIMER_A

 /*									Timer Counting Selection								
 ------------------------------------------------------------------*/
#define GPT_COUNT_DOWN				0
#define GPT_COUNT_UP					1
#define GPT_TIMER_COUNT_SELECTION					GPT_COUNT_DOWN

/*********************************************************************************************************
 *  									User Defined Data Type
 ********************************************************************************************************/
 
 /*									GPT Channel Selection							
 ------------------------------------------------------------------*/
typedef enum
{
	GPT_CHANNEL_0 	= 0,
	GPT_CHANNEL_1 	= 1,
	GPT_CHANNEL_2 	= 2,
	GPT_CHANNEL_3 	= 3,
	GPT_CHANNEL_4  	= 4,
	GPT_CHANNEL_5 	= 5,
	
	GPT_WIDE_CHANNEL_0 	= 6,
	GPT_WIDE_CHANNEL_1 	= 7,
	GPT_WIDE_CHANNEL_2 	= 8,
	GPT_WIDE_CHANNEL_3 	= 9,
	GPT_WIDE_CHANNEL_4  = 10,
	GPT_WIDE_CHANNEL_5 	= 11,
	
	GPT_CHANNEL_INVALID
	
}en_gpt_ch_id_t;

 /*									GPT Interrupt EN/DIS								
 ------------------------------------------------------------------*/
typedef enum
{
	GPT_IRQ_DISABLE = 0,
	GPT_IRQ_ENABLE  = 1,
	GPT_IRQ_INVALID
	
	
}en_gpt_irq_t;

 /*									GPT mode Selection								
 ------------------------------------------------------------------*/
typedef enum
{
	GPT_CH_MODE_ONE_SHOT 	= 0,
	GPT_CH_MODE_PERIODIC  = 1,
	GPT_CH_MODE_INVALID

}en_gpt_mode_t;

 /*									GPT mode Selection								
 ------------------------------------------------------------------*/
typedef enum
{
	GPT_STALL_DISABLE= 0,
	GPT_STALL_ENABLE  = 1,
	GPT_STALL_INVALID

}en_gpt_stall_t;

 /*									GPT mode Selection								
 ------------------------------------------------------------------*/
typedef enum
{
	GPT_TIME_US		= 0,
	GPT_TIME_MS  	= 1,
	GPT_TIME_S		= 2,
	GPT_TIME_INVALID

}en_gpt_time_x_t;



 /*									GPT Timer Configuration								
 ------------------------------------------------------------------*/
typedef struct
{
	en_gpt_ch_id_t				en_gpt_ch_id;
	en_gpt_mode_t					en_gpt_mode;
	en_gpt_stall_t				en_gpt_stall;
	en_gpt_time_x_t				en_gpt_time_x;
	uint32_ 							u32_set_time;
	en_gpt_irq_t 					en_gpt_irq;
	ptr_func_t						ptr_func;
	
}st_gpt_timer_cfg_t;

 /*									GPT PWM Configuration								
 ------------------------------------------------------------------*/
typedef struct
{
	en_gpt_ch_id_t				en_gpt_ch_id;
	en_gpt_stall_t				en_gpt_stall;
	uint32_ 							u32_set_time_ms;
	en_gpt_irq_t 					en_gpt_irq;
	ptr_func_t						ptr_func;
	
}st_gpt_pwm_cfg_t;

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
uint8_ 	GPT_u8Init(st_gpt_timer_cfg_t* st_gpt_timer_cfg);

/*****************************************************************************************************************
*											02- GPT_vidStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT Timer counter
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8Start(void);


/*****************************************************************************************************************
*											03- GPT_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_vidStop(void);


/*****************************************************************************************************************
*											04- GPT_vidIRQEnable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT enable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		GPT_vidIRQEnable(void);

/*****************************************************************************************************************
*											05- GPT_vidIRQDisable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT disable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		GPT_vidIRQDisable(void);

/*****************************************************************************************************************
*											06- GPT_u8GetCurrentVal()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get GPT current value
 * @in[1] 		: p_u8_int_status
								- Address of Variable which GPT current value to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_u8GetCurrentVal(uint64_* p_u64_int_cur_val );



void GPT_u8DutyCycle(uint32_ u32_a_duty_cycle);

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
uint8_ GPT_u8PWMInit(st_gpt_pwm_cfg_t* p_st_gpt_pwm_cfg);


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
uint8_ GPT_u8GeneratePWM(uint8_ copy_u8_duty_cycle);


/*****************************************************************************************************************
*											09- GPT_u8PWMStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start GPT PWM generation
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ GPT_u8PWMStart(void);


/*****************************************************************************************************************
*											10- GPT_u8PWMStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT PWM generation
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_u8PWMStop(void);

#endif /*GPT_INTERFACE_H_*/

