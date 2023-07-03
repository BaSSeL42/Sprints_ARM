
 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 13 - 6 - 2023
 *  Description 			: systick_Interface.h --> Function Prototypes
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
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_
/*********************************************************************************************************
 *  									Includes
 ********************************************************************************************************/
#include "LSTD_TYPES.h"

/*********************************************************************************************************
 *  									User Defined Data Type
 ********************************************************************************************************/
 
 /*									Systick Interrupt EN/DIS								
 ------------------------------------------------------------------*/
typedef enum
{
	SYSTK_IRQ_DISABLE = 0,
	SYSTK_IRQ_ENABLE  = 1,
	SYSTK_IRQ_INVALID
	
	
}en_systck_int_t;

 /*									Systick Source Clock Selection								
 ------------------------------------------------------------------*/
typedef enum
{
	SYSTK_PIOSC = 0,
	SYSTK_SYSTEM_CLK  = 1,
	SYSTK_CLK_SRC_INVALID
	
	
}en_systck_clk_src_t;

 /*									Systick Timer Configuration								
 ------------------------------------------------------------------*/
typedef struct
{
	en_systck_clk_src_t		en_systck_clk_src;
	en_systck_int_t 			en_systck_int;
	uint32_								u32_time_ms;
	ptr_func_t						ptr_func;
	
}st_systk_cfg_t;


/********************************************************************************************************************
 *  										APIs ProtoType
*******************************************************************************************************************/

/*****************************************************************************************************************
*											01- SYSTICK_u8Init()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Systick Timer Intialization
 * @in[1] 		: Address of struct Instance
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	SYSTICK_u8Init(st_systk_cfg_t* st_systk_cfg);

/*****************************************************************************************************************
*											02- SYSTICK_vidStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start Timer count
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ SYSTICK_vidStart(void);

/*****************************************************************************************************************
*											03- SYSTICK_vidResetTimer()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Systick Reset Counter and start from beginning
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		SYSTICK_vidResetTimer(void);

/*****************************************************************************************************************
*											04- SYSTICK_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop Systick Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		SYSTICK_vidStop(void);

/*****************************************************************************************************************
*											05- SYSTICK_u8GetIntStatus()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get Systick Interrupt Flag to poll on it
 * @in[1] 		: p_u8_int_status
								- Address of Variable which interrupt state to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ 	SYSTICK_u8GetIntStatus(uint8_* p_u8_int_status );



/*****************************************************************************************************************
*											06- SYSTICK_u8DeInit()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: De-Initialize Systick Timer
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void 		SYSTICK_u8DeInit(void);


#endif /*SYSTICK_INTERFACE_H_*/


