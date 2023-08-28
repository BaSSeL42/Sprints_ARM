#include "SYS_CONTROL_interface.h"
#include "SYS_CONTROL_private.h"



void sys_control_set_clock_system(sys_control_str_config_t *ptr_str_sys_control_config){
	
	
	CLR_BIT(SYS_CONTROL_RCC2, USERCC2);
	
	if(ptr_str_sys_control_config->prescaller > 1){
		SET_BIT(SYS_CONTROL_RCC, USESYSDIV);
		SYS_CONTROL_RCC = (SYS_CONTROL_RCC&(~(0xF << SYSDIV)))| (ptr_str_sys_control_config->prescaller<<SYSDIV);
	}else{
		CLR_BIT(SYS_CONTROL_RCC, USESYSDIV);
	}
	SET_BIT(SYS_CONTROL_RCC, BYPASS);
	SYS_CONTROL_RCC = (SYS_CONTROL_RCC&(~(0x3 << OSCSRC)))| (ptr_str_sys_control_config->enu_OSCSRC<<OSCSRC);
	
	SET_BIT(SYS_CONTROL_RCC, PWRDN);
	
	
}
