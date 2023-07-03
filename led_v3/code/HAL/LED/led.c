/*
 *		File		: led.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: LED functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
//#include "mgpio_Interface.h"
#include "led.h"



/***********************************************************************************************
*															Global Variables
***********************************************************************************************/
st_gpio_cfg_t str_dio_led_init;

/***********************************************************************************************
*										Function Implementation
***********************************************************************************************/
enu_ledError_t HLed_Init(enu_pin_t en_pinNum)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinNum < MGPIO_PIN_INVALID )
	{
		str_dio_led_init.enu_pin 													= en_pinNum;
		str_dio_led_init.enu_gpio_mode										= MGPIO_MODE_DIGITAL;
		str_dio_led_init.enu_pin_dir_mode									= MGPIO_DIR_OUTPUT;
		str_dio_led_init.un_gpio_conf.enu_gpio_amp_mode		= MGPIO_MAMP_8;
		
		errorStatus &= MGPIO_u8Init(&str_dio_led_init);
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}

enu_ledError_t HLed_on(enu_pin_t en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		errorStatus &= MGPIO_u8SetPinData(en_pinx, MGPIO_PIN_HIGH);
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}



enu_ledError_t HLed_off(enu_pin_t en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		errorStatus &= MGPIO_u8SetPinData(en_pinx, MGPIO_PIN_LOW);
	}
	else
	{
		errorStatus = LED_NOK;
	}



	return errorStatus;

}


enu_ledError_t HLed_toggle(enu_pin_t en_pinx)
{
	enu_ledError_t errorStatus = LED_OK;

	if ( en_pinx < MGPIO_PIN_INVALID )
	{
		errorStatus &= MGPIO_u8SetPinData(en_pinx, MGPIO_PIN_TOG);

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
