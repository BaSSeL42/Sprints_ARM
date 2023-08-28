/*
 *		File		: led.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: LED functions Implementation
 */
/************************************************************************************************
*											Includes
***********************************************************************************************/
#include "std_types.h"
#include "bit_math.h"
//#include "mgpio_Interface.h"
#include "led.h"



/***********************************************************************************************
*															Global Variables
***********************************************************************************************/
#define LED_MAX_NUM		5
dio_str_pin_Config_t str_dio_led_init[LED_MAX_NUM];
dio_str_output_type_and_speed_and_state_t str_led_output_type_and_speed_and_state = 
{
	.enu_output_type = DIO_PIN_OUTPUT_PUSH_PULL,
	.enu_output_current = DIO_PIN_2MA,
	.enu_pin_state = DIO_PIN_LOW_STATE
};
/***********************************************************************************************
*										Function Implementation
***********************************************************************************************/
enu_ledError_t HLED_Init(str_led_config_t *str_led_config)
{
	uint8_ errorStatus = LED_OK;

	if(NULL != str_led_config)
	{
		str_dio_led_init[str_led_config->u8_led_id].enu_pin = str_led_config->enu_pin;
		str_dio_led_init[str_led_config->u8_led_id].enu_port = str_led_config->enu_port;
		str_dio_led_init[str_led_config->u8_led_id].enu_pin_mode = DIO_PIN_OUTPUT;
		str_dio_led_init[str_led_config->u8_led_id].un_input_output_type.str_output_type_and_speed_and_state.enu_output_type = str_led_output_type_and_speed_and_state.enu_output_type;
		str_dio_led_init[str_led_config->u8_led_id].un_input_output_type.str_output_type_and_speed_and_state.enu_output_current = str_led_output_type_and_speed_and_state.enu_output_current;
		str_dio_led_init[str_led_config->u8_led_id].un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = str_led_output_type_and_speed_and_state.enu_pin_state;
		
		
		dio_enable_clock(str_led_config->enu_port);
		errorStatus = dio_init_pin(&str_dio_led_init[str_led_config->u8_led_id]);
	}
	else
	{
		errorStatus = LED_NOK;
	}
	
	if(LED_OK != errorStatus)
		errorStatus = LED_NOK;
	
	
	return errorStatus;

}

enu_ledError_t HLED_on(uint8_ u8_led_id)
{
	uint8_ errorStatus = LED_OK;

	if ( u8_led_id < LED_MAX_NUM )
	{
		errorStatus = dio_set_pin(&str_dio_led_init[u8_led_id],DIO_PIN_HIGH_STATE);
	}
	else
	{
		errorStatus = LED_NOK;
	}
	
	if(LED_OK != errorStatus)
		errorStatus = LED_NOK;

	return errorStatus;

}



enu_ledError_t HLED_off(uint8_ u8_led_id)
{
	uint8_ errorStatus = LED_OK;

	if ( u8_led_id < LED_MAX_NUM )
	{
		errorStatus = dio_set_pin(&str_dio_led_init[u8_led_id],DIO_PIN_LOW_STATE);
	}
	else
	{
		errorStatus = LED_NOK;
	}
	
	if(LED_OK != errorStatus)
		errorStatus = LED_NOK;

	return errorStatus;

}


enu_ledError_t HLED_toggle(uint8_ u8_led_id)
{
	uint8_ errorStatus = LED_OK;

	if ( u8_led_id < LED_MAX_NUM )
	{
		errorStatus = dio_toggle_pin(&str_dio_led_init[u8_led_id]);
	}
	else
	{
		errorStatus = LED_NOK;
	}
	
	if(LED_OK != errorStatus)
		errorStatus = LED_NOK;

	return errorStatus;

}
/***********************************************************************************************
*												END
***********************************************************************************************/
