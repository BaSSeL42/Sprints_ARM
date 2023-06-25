#include "DIO_private.h"
#include "DIO_interface.h"




static uint32_t dio_get_base_address(dio_enu_portx_t copy_enu_port_num){
	uint32_t l_dio_base_address = 0;





	return l_dio_base_address;
}
dio_enu_return_state_t  dio_unlock_special_pin(dio_str_pin_Config_t *ptr_str_pinconfig){
	dio_enu_return_state_t return_value = DIO_OK;
	uint32_t l_un32_gpio_base_address=0;
	if(ptr_str_pinconfig != NULL)
	{
		







	}else{
	}
  return return_value;
}

dio_enu_return_state_t  dio_enable_clock(dio_enu_portx_t copy_enu_port_num){
	dio_enu_return_state_t return_value = DIO_OK;
	if(copy_enu_port_num< MAX_INVALID_PORT)
	{
		


	}else{
	}
  return return_value;
}
dio_enu_return_state_t  dio_init_pin(dio_str_pin_Config_t *ptr_str_pinconfig){
  dio_enu_return_state_t return_value = DIO_OK;

	
	if(ptr_str_pinconfig != NULL){
		
		

		
	
	}else{
		return_value = DIO_NULL_PTR;
	}
		
   return return_value;
}
dio_enu_return_state_t  dio_set_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t copy_enu_pin_state){
    dio_enu_return_state_t return_value = DIO_OK;

	
	
    if( ptr_str_pinconfig != NULL){
			
			
		}else{
			return_value = DIO_NULL_PTR;
		}
    return return_value;
}

dio_enu_return_state_t  dio_toggle_pin(dio_str_pin_Config_t *ptr_str_pinconfig){
		dio_enu_return_state_t return_value = DIO_OK;

	
	
    if( ptr_str_pinconfig != NULL){
			
			
			
		
		}else{
			return_value = DIO_NULL_PTR;
		}
    return return_value;

}
dio_enu_return_state_t  dio_read_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t *ptr_enu_pin_state){
    dio_enu_return_state_t return_value = DIO_OK;

    if(ptr_str_pinconfig != NULL){

 
    }else{
        return_value = DIO_NULL_PTR;
    }

    return return_value;
}