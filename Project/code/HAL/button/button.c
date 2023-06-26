/*
 *		File		: button.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: Button functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/

#include "button.h"




/***********************************************************************************************
*										Functions Implementation
***********************************************************************************************/
enu_buttonError_t HButton_Init(button_str_btn_config_t *en_pinx)
{
	enu_buttonError_t return_value = BTN_OK;
    if(en_pinx == NULL ){
        return_value =BTN_NULL_PTR;
    }
    else{
				dio_str_pin_Config_t temp = {.enu_port = en_pinx->port_name,
																		 .enu_pin = en_pinx->pin,
																		 .enu_pin_mode = DIO_PIN_INPUT,
																		 .un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP};
				if(en_pinx->button_active == BUTTON_ACTIVE_LOW){
					temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP;
				}else{
					temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_DOWN;
				}
        dio_init_pin(&temp);
    }

    return return_value;
}


enu_buttonError_t HButton_getPinVal(button_str_btn_config_t *en_pinx,  btn_enu_btn_state_t* enu_refVal)
{
	enu_buttonError_t ret = BTN_OK;
	dio_enu_pin_state_t l_enu_pin_state;
    if(en_pinx == NULL  || enu_refVal == NULL){
        ret =BTN_NOT_OK;
    }
    else{
        dio_str_pin_Config_t temp = {.enu_port = en_pinx->port_name,
																		 .enu_pin = en_pinx->pin,
																		 .enu_pin_mode = DIO_PIN_INPUT,
																		 .un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP};
				if(en_pinx->button_active == BUTTON_ACTIVE_LOW){
					temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP;
				}else{
					temp.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_DOWN;
				}
				
        dio_read_pin( &temp, &l_enu_pin_state);
        if(((en_pinx->button_active == BUTTON_ACTIVE_LOW)&&(l_enu_pin_state == DIO_PIN_LOW_STATE))||
						((en_pinx->button_active == BUTTON_ACTIVE_HIGH)&&(l_enu_pin_state == DIO_PIN_HIGH_STATE)) ){
            *enu_refVal = BUTTON_PRESSED ;
        }else{
            *enu_refVal = BUTTON_RELEASED ;
        }
    }

    return ret;

}



enu_buttonError_t HButton_initializa_with_int(const button_str_btn_config_t* ptr_str_btn_config , ptr_func_t ptr_callback){
    
	enu_buttonError_t ret = BTN_OK;
	exit_str_pin_Config_t l_btn;
    if(ptr_str_btn_config == NULL ){
        ret =BTN_NULL_PTR;
    }
    else{
					l_btn.enu_port = ptr_str_btn_config->port_name;
					l_btn.enu_pin	=	 ptr_str_btn_config->pin;
					if(ptr_str_btn_config->button_active == BUTTON_ACTIVE_LOW){
						l_btn.enu_idle_state = EXIT_PULL_UP;
						l_btn.enu_trigger_mode = EXIT_FALLING_EDGE;
					}else if(ptr_str_btn_config->button_active == BUTTON_ACTIVE_HIGH){
						l_btn.enu_idle_state = EXIT_PULL_DOWN;
						l_btn.enu_trigger_mode = EXIT_RISING_EDGE;
					}
					
					exit_init_pin(&l_btn);
					exit_set_callback(&l_btn, ptr_callback);
					
    }

    return ret;
}


enu_buttonError_t HButton_enable_INT( button_str_btn_config_t* ptr_str_btn_config){
	enu_buttonError_t ret = BTN_OK;
		exit_str_pin_Config_t l_btn;
    if(ptr_str_btn_config == NULL ){
        ret =BTN_NULL_PTR;
    }
    else{
					l_btn.enu_port = ptr_str_btn_config->port_name;
					l_btn.enu_pin	=	 ptr_str_btn_config->pin;
					exit_enable_int(&l_btn);
    }

    return ret;
}

enu_buttonError_t HButton_disable_INT( button_str_btn_config_t* ptr_str_btn_config){
	enu_buttonError_t ret = BTN_OK;
		exit_str_pin_Config_t l_btn;
    if(ptr_str_btn_config == NULL ){
        ret =BTN_NULL_PTR;
    }
    else{
					l_btn.enu_port = ptr_str_btn_config->port_name;
					l_btn.enu_pin	=	 ptr_str_btn_config->pin;
					exit_disable_int(&l_btn);
    }

    return ret;
}
/***********************************************************************************************
*										END
***********************************************************************************************/
