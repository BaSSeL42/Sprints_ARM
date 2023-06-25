/*
 *		File		: button.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: Button functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "../../COM/std_types.h"
#include "../../COM/bit_math.h"
//#include "mgpio_Interface.h"
#include "./include/button.h"




st_gpio_cfg_t str_dio_button_init;

/***********************************************************************************************
*										Functions Implementation
***********************************************************************************************/
enu_buttonError_t HButton_Init(enu_pin_t en_pinx)
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{

	}
	else
	{
		errorStatus = BUTTON_NOK;
	}

	return errorStatus;
}


enu_buttonError_t HButton_getPinVal(enu_pin_t en_pinx,  uint8_* pu8_refVal )
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < MGPIO_PIN_INVALID && pu8_refVal != NULL )
	{
		
	}
	else
	{
		errorStatus = BUTTON_NOK;
	}

	return errorStatus;

}

/***********************************************************************************************
*										END
***********************************************************************************************/
