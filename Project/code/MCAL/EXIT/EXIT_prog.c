#include "EXIT_private.h"
#include "EXIT_interface.h"



static ptr_vfunc exit_callback[7] ={NULL};
static exit_special_pin special_pins[1]= {{.enu_port = DIO_PORTF, .enu_pin = DIO_PIN_0 }};

void GPIOF_Handler(void){
			
			
}

static uint32_t exit_get_base_address(dio_enu_portx_t copy_enu_port_num){
	uint32_t l_dio_base_address = 0;

	return l_dio_base_address;
}



exit_enu_return_state_t  exit_init_pin(exit_str_pin_Config_t *ptr_str_pin_config){
	exit_enu_return_state_t return_value = EXIT_OK;
	
		
	}else{
		return_value = EXIT_NULL_PTR;
	}
	return	return_value;
}





exit_enu_return_state_t  exit_enable_int(exit_str_pin_Config_t *ptr_str_pin_config){
	exit_enu_return_state_t return_value = EXIT_OK;

	return	return_value;
}



exit_enu_return_state_t  exit_disable_int(exit_str_pin_Config_t *ptr_str_pin_config){
		exit_enu_return_state_t return_value = EXIT_OK;
		uint32_t l_u32_dio_base_address = 0;
	if(ptr_str_pin_config != NULL){

	}else{
		return_value = EXIT_NULL_PTR;

	}
	return	return_value;
}
exit_enu_return_state_t  exit_set_callback(exit_str_pin_Config_t *ptr_str_pin_config, ptr_vfunc ptr_call_back){
	exit_enu_return_state_t return_value = EXIT_OK;

	if(ptr_call_back != NULL){

	
	}else{
		return_value = EXIT_NULL_PTR;
	}
	return	return_value;

}