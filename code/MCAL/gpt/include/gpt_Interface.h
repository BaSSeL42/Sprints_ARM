
 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 13 - 6 - 2023
 *  Description 			: gpt_Interface.h --> Function Prototypes
 *  Module Features		:
 *  											01- SYSTICK_u8Init()
 *  											02- SYSTICK_vidStart()
													03-	SYSTICK_vidResetTimer()
													04-	SYSTICK_vidStop()
													05-	SYSTICK_u8GetIntStatus()
													06-	SYSTICK_u8DeInit()
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
 /*									Timer Type Selection								
 ------------------------------------------------------------------*/
#define GPT_TIMER_A							0
#define GPT_TIMER_B							1
#define GPT_TIMER_SELECTION				GPT_TIMER_A
 /*									Timer Concatination ENABLE/DISABLE								
 ------------------------------------------------------------------*/
#define GPT_TIMER_INDVIDUAL				0
#define GPT_TIMER_CONCATINATION		1
#define GPT_TIMER_CONC_SELECTION					GPT_TIMER_CONCATINATION

 /*									Timer Counting Selection								
 ------------------------------------------------------------------*/
#define GPT_COUNT_DOWN				0
#define GPT_COUNT_UP					1
#define GPT_TIMER_COUNT_SELECTION					GPT_COUNT_UP

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



 /*									Systick Timer Configuration								
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


/********************************************************************************************************************
 *  										APIs ProtoType
*******************************************************************************************************************/

/*****************************************************************************************************************
*											01- SYSTICK_u8Init()									
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
uint8_ GPT_vidStart(void);


/*****************************************************************************************************************
*											03- GPT_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop GPT Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void GPT_vidStop(void);


/*****************************************************************************************************************
*											05- GPT_vidIRQEnable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT enable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		GPT_vidIRQEnable(void);

/*****************************************************************************************************************
*											06- GPT_vidIRQDisable()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: GPT disable IRQ
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		GPT_vidIRQDisable(void);

/*****************************************************************************************************************
*											07- GPT_u8GetCurrentVal()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get GPT current value
 * @in[1] 		: p_u8_int_status
								- Address of Variable which GPT current value to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	GPT_u8GetCurrentVal(uint64_* p_u64_int_cur_val );




#endif /*GPT_INTERFACE_H_*/