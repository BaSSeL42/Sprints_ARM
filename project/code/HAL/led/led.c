/*
 *		File		: led.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: LED functions Implementation
 */
/************************************************************************************************
*											Includes
***********************************************************************************************/
#include "../../COM/std_types.h"
#include "../../COM/bit_math.h"
//#include "mgpio_Interface.h"
#include "../include/led.h"



/***********************************************************************************************
*															Global Variables
***********************************************************************************************/
st_gpio_cfg_t str_dio_led_init;

/***********************************************************************************************
*										Function Implementation
***********************************************************************************************/
enu_ledError_t HLED_Init(enu_pin_t en_pinNum)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinNum < MGPIO_PIN_INVALID )
	{

	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}

enu_ledError_t HLED_on(enu_pin_t en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}



enu_ledError_t HLED_off(enu_pin_t en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}


enu_ledError_t HLED_toggle(enu_pin_t en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		

	}
	else
	{
		errorStatus = LED_NOK;
	}

	return errorStatus;

}
/***********************************************************************************************
*												END
***********************************************************************************************/
