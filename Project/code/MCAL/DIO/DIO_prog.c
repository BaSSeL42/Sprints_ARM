#include "DIO_private.h"
#include "DIO_interface.h"




static uint32_ dio_get_base_address(dio_enu_portx_t copy_enu_port_num){
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

dio_enu_return_state_t  dio_unlock_special_pin(dio_str_pin_Config_t *ptr_str_pinconfig){
	dio_enu_return_state_t return_value = DIO_OK;
	uint32_ l_un32_gpio_base_address=0;
	
	if(ptr_str_pinconfig != NULL)
	{
		l_un32_gpio_base_address = dio_get_base_address(ptr_str_pinconfig->enu_port);
		
		HWREG32(l_un32_gpio_base_address + GPIOLOCK) = VALUE_TO_UNLOCK;
		SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOCR), ptr_str_pinconfig->enu_pin);
		HWREG32(l_un32_gpio_base_address + GPIOLOCK) = 0;
	}else{
	}
  return return_value;
}

dio_enu_return_state_t  dio_enable_clock(dio_enu_portx_t copy_enu_port_num){
	dio_enu_return_state_t return_value = DIO_OK;
	if(copy_enu_port_num< MAX_INVALID_PORT)
	{
		SET_BIT(RCGCGPIO, copy_enu_port_num);
	}else{
	}
  return return_value;
}


dio_enu_return_state_t  dio_init_pin(dio_str_pin_Config_t *ptr_str_pinconfig){
  dio_enu_return_state_t return_value = DIO_OK;
	uint32_ l_un32_gpio_base_address=0;
	dio_enu_output_current_t l_output_current;
	dio_enu_input_type_t l_enu_input_type; 
	dio_enu_pin_state_t l_enu_pin_state;
	
	if(ptr_str_pinconfig != NULL){
		l_un32_gpio_base_address = dio_get_base_address(ptr_str_pinconfig->enu_port);
		SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODEN),ptr_str_pinconfig->enu_pin);
		
		HWREG32(l_un32_gpio_base_address + GPIOPCTL) &=  ~(((uint32_)0xF)<<(ptr_str_pinconfig->enu_pin * 4));
		
		if(ptr_str_pinconfig->enu_pin_mode == DIO_PIN_OUTPUT){
			
			SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODIR), ptr_str_pinconfig->enu_pin);
			
			l_output_current = ptr_str_pinconfig->un_input_output_type.str_output_type_and_speed_and_state.enu_output_current;
			
			
			if(l_output_current == DIO_PIN_2MA){
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODR2R), ptr_str_pinconfig->enu_pin);
			}else if(l_output_current == DIO_PIN_4MA){
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODR4R), ptr_str_pinconfig->enu_pin);
			}else if(l_output_current == DIO_PIN_8MA){
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIODR8R), ptr_str_pinconfig->enu_pin);
			}else{
				
			}
			
			l_enu_pin_state = ptr_str_pinconfig->un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state;
			dio_set_pin(ptr_str_pinconfig, l_enu_pin_state);
		
		}else if(ptr_str_pinconfig->enu_pin_mode == DIO_PIN_INPUT){
			CLR_BIT(HWREG32(l_un32_gpio_base_address + GPIODIR),ptr_str_pinconfig->enu_pin);
			l_enu_input_type = ptr_str_pinconfig->un_input_output_type.enu_input_type;
			if(l_enu_input_type == DIO_PIN_INPUT_PULL_UP){
				
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPUR), ptr_str_pinconfig->enu_pin);
			}else if(l_enu_input_type == DIO_PIN_INPUT_PULL_DOWN){
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPDR), ptr_str_pinconfig->enu_pin);
			}else{
			
			}
				
		}else{
		
		}
		
	
	}else{
		return_value = DIO_NULL_PTR;
	}
		
   return return_value;
}
dio_enu_return_state_t  dio_set_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t copy_enu_pin_state){
    dio_enu_return_state_t return_value = DIO_OK;
		uint32_ l_un32_gpio_base_address=0;
	
	
    if( ptr_str_pinconfig != NULL){
			
			l_un32_gpio_base_address = dio_get_base_address(ptr_str_pinconfig->enu_port);
			if(copy_enu_pin_state == DIO_PIN_HIGH_STATE){
				
				HWREG32(l_un32_gpio_base_address + GPIODATA+(1<<(ptr_str_pinconfig->enu_pin+2))) =  (DIO_PIN_HIGH_STATE<<ptr_str_pinconfig->enu_pin);
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPUR), ptr_str_pinconfig->enu_pin);
			}else if(copy_enu_pin_state == DIO_PIN_LOW_STATE){
				HWREG32(l_un32_gpio_base_address + GPIODATA+(1<<(ptr_str_pinconfig->enu_pin+2))) =  DIO_PIN_LOW_STATE;
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPDR), ptr_str_pinconfig->enu_pin);
			}
		}else{
			return_value = DIO_NULL_PTR;
		}
    return return_value;
}

dio_enu_return_state_t  dio_toggle_pin(dio_str_pin_Config_t *ptr_str_pinconfig){
		dio_enu_return_state_t return_value = DIO_OK;
		uint32_ l_un32_gpio_base_address=0;
		dio_enu_pin_state_t l_enu_pin_state;
	
	
    if( ptr_str_pinconfig != NULL){
			
			l_un32_gpio_base_address = dio_get_base_address(ptr_str_pinconfig->enu_port);
			dio_read_pin(ptr_str_pinconfig, &l_enu_pin_state);
			if(l_enu_pin_state != DIO_PIN_HIGH_STATE){
				HWREG32(l_un32_gpio_base_address + GPIODATA+(1<<(ptr_str_pinconfig->enu_pin+2))) =  (DIO_PIN_HIGH_STATE<<ptr_str_pinconfig->enu_pin);
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPUR), ptr_str_pinconfig->enu_pin);
			}else if(l_enu_pin_state != DIO_PIN_LOW_STATE){
				HWREG32(l_un32_gpio_base_address + GPIODATA+(1<<(ptr_str_pinconfig->enu_pin+2))) =  DIO_PIN_LOW_STATE;
				SET_BIT(HWREG32(l_un32_gpio_base_address + GPIOPDR), ptr_str_pinconfig->enu_pin);
			}
		}else{
			return_value = DIO_NULL_PTR;
		}
    return return_value;

}


dio_enu_return_state_t  dio_read_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t *ptr_enu_pin_state){
    dio_enu_return_state_t return_value = DIO_OK;
		uint32_ l_un32_gpio_base_address=0;
    if(ptr_str_pinconfig != NULL){

		l_un32_gpio_base_address = dio_get_base_address(ptr_str_pinconfig->enu_port);
				
		*ptr_enu_pin_state = (HWREG32(l_un32_gpio_base_address + GPIODATA+(1<<(ptr_str_pinconfig->enu_pin+2)))>>ptr_str_pinconfig->enu_pin);
    }else{
        return_value = DIO_NULL_PTR;
    }

    return return_value;
}
