/*
 *		File		: button.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: Button functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
//#include "mgpio_Interface.h"
#include "button.h"




st_gpio_cfg_t str_dio_button_init;

/***********************************************************************************************
*										Functions Implementation
***********************************************************************************************/
enu_buttonError_t HButton_Init(enu_pin_t en_pinx)
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		str_dio_button_init.enu_pin 													= en_pinx;
		str_dio_button_init.enu_gpio_mode										  = MGPIO_MODE_DIGITAL;
		str_dio_button_init.enu_pin_dir_mode									= MGPIO_DIR_INPUT;
		str_dio_button_init.un_gpio_conf.u8_input_pull_type 	= MGPIO_PULL_UP;

		errorStatus &= MGPIO_u8Init(&str_dio_button_init);
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
		errorStatus &= MGPIO_u8GetPinData(en_pinx, pu8_refVal);
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
