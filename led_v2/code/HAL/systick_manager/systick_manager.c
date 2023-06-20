 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 14 - 6 - 2023
 *  Description 			: systick_source.c --> APIs implementation
 *  Module Features		:
 *  											01- SYSTICK_MANAGER_u8Init()
 *  											02- SYSTICK_MANAGER_vidStart()
													03-	SYSTICK_MANAGER_vidResetTimer()
													04-	SYSTICK_MANAGER_vidStop()
													05-	SYSTICK_MANAGER_u8GetIntStatus()
													06-	SYSTICK_MANAGER_u8DeInit()
 *****************************************************************************/
 
/********************************************************************************************************************
*												Peripheral Files
********************************************************************************************************************/
#include "systick_manager.h"



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
uint8_ 	SYSTICK_MANAGER_u8Init(st_systk_cfg_t* st_systk_cfg)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state = SYSTICK_u8Init(st_systk_cfg);
	
	return loc_u8_err_state;
}

/*****************************************************************************************************************
*											02- SYSTICK_vidStart()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Start Timer count
 * @in[1] 			: void
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ SYSTICK_MANAGER_vidStart(void)
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state = SYSTICK_vidStart();
	
	return loc_u8_err_state;
}

/*****************************************************************************************************************
*											03- SYSTICK_vidResetTimer()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Systick Reset Counter and start from beginning
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void SYSTICK_MANAGER_vidResetTimer(void)
{
	SYSTICK_vidResetTimer();
}


/*****************************************************************************************************************
*											04- SYSTICK_vidStop()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: Stop Systick Timer Counter
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void SYSTICK_MANAGER_vidStop(void)
{
	SYSTICK_vidStop();
}



/*****************************************************************************************************************
*											05- SYSTICK_u8GetIntStatus()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  		: Get Systick Interrupt Flag to poll on it
 * @in[1] 		: p_u8_int_status
								- Address of Variable which interrupt state to be stored 
 * @return    : uint8_  [error status Sucessful Operation return {SUCCESS} if not return {FAILED}]
 ******************************************************************************************************************/
uint8_ SYSTICK_MANAGER_u8GetIntStatus(uint8_* p_u8_int_status )
{
	uint8_ loc_u8_err_state = SUCCESS;
	
	loc_u8_err_state = SYSTICK_u8GetIntStatus(p_u8_int_status);
	
	return loc_u8_err_state;
	
}
/*****************************************************************************************************************
*											06- SYSTICK_u8DeInit()									
* ----------------------------------------------------------------------------------------------------------------
 * @func  			: De-Initialize Systick Timer
 * @in[1] 			: void
 * @return    	: void
 ******************************************************************************************************************/
void SYSTICK_MANAGER_u8DeInit(void)
{
	SYSTICK_u8DeInit();
}


