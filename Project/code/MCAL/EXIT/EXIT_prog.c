#include "EXIT_private.h"
#include "EXIT_interface.h"



static ptr_func_t exit_callback[7] ={NULL};
static exit_special_pin special_pins[1]= {{.enu_port = DIO_PORTF, .enu_pin = DIO_PIN_0 }};

void GPIOF_Handler(void){
			if(GET_BIT(HWREG32(DIO_PORTF_APB + GPIOMIS),DIO_PIN_0) == 1){
				if(exit_callback[0] != NULL){
					exit_callback[0]();
				}
				SET_BIT(HWREG32(DIO_PORTF_APB + GPIOICR),DIO_PIN_0);
			}
			if(GET_BIT(HWREG32(DIO_PORTF_APB + GPIOMIS),DIO_PIN_4) == 1){
				if(exit_callback[4] != NULL){
					exit_callback[4]();
				}
				SET_BIT(HWREG32(DIO_PORTF_APB + GPIOICR),DIO_PIN_4);
			}
			
}

static uint32_ exit_get_base_address(dio_enu_portx_t copy_enu_port_num){

	uint32_ l_dio_base_address = 0;
	switch(copy_enu_port_num){
				
				case DIO_PORTA:
					l_dio_base_address = DIO_PORTA_APB;	
					break;
				
				case DIO_PORTB:
					l_dio_base_address = DIO_PORTB_APB;	
					break;
				
				case DIO_PORTC:
					l_dio_base_address = DIO_PORTC_APB;	
					break;
				
				case DIO_PORTD:
					l_dio_base_address = DIO_PORTD_APB;	
					break;
				
				case DIO_PORTE:
					l_dio_base_address = DIO_PORTE_APB;	
					break;
				
				case DIO_PORTF:
					l_dio_base_address = DIO_PORTF_APB;	
					break;
			
				default:
					break;
			}
	return l_dio_base_address;
}



exit_enu_return_state_t  exit_init_pin(exit_str_pin_Config_t *ptr_str_pin_config){
	exit_enu_return_state_t return_value = EXIT_OK;
	uint32_ l_u32_dio_base_address = 0;
	dio_str_pin_Config_t l_str_pinconfig;
	nvic_enu_interupt_index_t l_enu_interupt_index;
	if(ptr_str_pin_config != NULL){
		l_str_pinconfig.enu_pin = ptr_str_pin_config->enu_pin;
		l_str_pinconfig.enu_port = ptr_str_pin_config->enu_port;
		l_str_pinconfig.enu_pin_mode = DIO_PIN_INPUT;
		
		if(ptr_str_pin_config->enu_idle_state == EXIT_PULL_UP){
			l_str_pinconfig.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_UP; 
		}else if(ptr_str_pin_config->enu_idle_state == EXIT_PULL_DOWN){
			l_str_pinconfig.un_input_output_type.enu_input_type = DIO_PIN_INPUT_PULL_DOWN;
		}else if(ptr_str_pin_config->enu_idle_state == EXIT_OPEN_DRAIN){
			l_str_pinconfig.un_input_output_type.enu_input_type = DIO_PIN_INPUT_NO_PULL_UP_NO_PULL_DOWN;
		}else{
		
		}
		dio_enable_clock(l_str_pinconfig.enu_port);
		l_u32_dio_base_address = exit_get_base_address(ptr_str_pin_config->enu_port);
		if((special_pins[0].enu_pin == ptr_str_pin_config->enu_pin)&&(special_pins[0].enu_port ==ptr_str_pin_config->enu_port)){
			dio_unlock_special_pin(&l_str_pinconfig);
		}
		dio_init_pin(&l_str_pinconfig);
		
		CLR_BIT(HWREG32(l_u32_dio_base_address + GPIOIM),l_str_pinconfig.enu_pin);
		CLR_BIT(HWREG32(l_u32_dio_base_address + GPIOIS),l_str_pinconfig.enu_pin);
		if(ptr_str_pin_config->enu_trigger_mode == EXIT_RISING_EDGE){
			
			SET_BIT(HWREG32(l_u32_dio_base_address + GPIOIEV),l_str_pinconfig.enu_pin);
		
		}else if (ptr_str_pin_config->enu_trigger_mode == EXIT_FALLING_EDGE){
			
			CLR_BIT(HWREG32(l_u32_dio_base_address + GPIOIEV),l_str_pinconfig.enu_pin);
			
		}else if(ptr_str_pin_config->enu_trigger_mode == EXIT_BOTH_EDGE){
			SET_BIT(HWREG32(l_u32_dio_base_address + GPIOIBE),l_str_pinconfig.enu_pin);
		}else{
		}
		SET_BIT(HWREG32(l_u32_dio_base_address + GPIOICR),l_str_pinconfig.enu_pin);
		switch(l_str_pinconfig.enu_port){
			case DIO_PORTA:
				l_enu_interupt_index = GPIO_A;
				break;
			case DIO_PORTB:
				l_enu_interupt_index = GPIO_B;
				break;
			case DIO_PORTC:
				l_enu_interupt_index = GPIO_C;
				break;
			case DIO_PORTD:
				l_enu_interupt_index = GPIO_D;
				break;
			case DIO_PORTE:
				l_enu_interupt_index = GPIO_E;
				break;
			case DIO_PORTF:
				l_enu_interupt_index = GPIO_F;
				break;
			default:
				break;
		}

		nvic_EnablePeripheral(l_enu_interupt_index);
		
	}else{
		return_value = EXIT_NULL_PTR;
	}
	return	return_value;
}





exit_enu_return_state_t  exit_enable_int(exit_str_pin_Config_t *ptr_str_pin_config){
	exit_enu_return_state_t return_value = EXIT_OK;
	uint32_ l_u32_dio_base_address = 0;
	if(ptr_str_pin_config != NULL){
			l_u32_dio_base_address = exit_get_base_address(ptr_str_pin_config->enu_port);
			SET_BIT(HWREG32(l_u32_dio_base_address + GPIOIM),ptr_str_pin_config->enu_pin);
	
		}else{
		return_value = EXIT_NULL_PTR;
	}
	return	return_value;
}



exit_enu_return_state_t  exit_disable_int(exit_str_pin_Config_t *ptr_str_pin_config){
	exit_enu_return_state_t return_value = EXIT_OK;
	uint32_ l_u32_dio_base_address = 0;
	if(ptr_str_pin_config != NULL){
			l_u32_dio_base_address = exit_get_base_address(ptr_str_pin_config->enu_port);
			CLR_BIT(HWREG32(l_u32_dio_base_address + GPIOIM),ptr_str_pin_config->enu_pin);
	
		}else{
		return_value = EXIT_NULL_PTR;
	}
	return	return_value;
}
exit_enu_return_state_t  exit_set_callback(exit_str_pin_Config_t *ptr_str_pin_config, ptr_func_t ptr_call_back){
	exit_enu_return_state_t return_value = EXIT_OK;

	if(ptr_call_back != NULL){
			exit_callback[ptr_str_pin_config->enu_pin] = ptr_call_back;
	
	}else{
		return_value = EXIT_NULL_PTR;
	}
	return	return_value;

}