#ifndef SYS_CONTROL_INTERFACE_H
#define	SYS_CONTROL_INTERFACE_H


#include "../../COM/bit_math.h"
#include "../../COM/std_types.h"

typedef enum{
	SYS_CONTROL_MOSC=0,
	SYS_CONTROL_PIOSC=1,
	SYS_CONTROL_PIOSC_4=2,
	SYS_CONTROL_LFIOSC=3
	
}sys_control_enu_OSCSRC_t;



typedef struct{
	uint8_ prescaller :4;
	sys_control_enu_OSCSRC_t  enu_OSCSRC;
}sys_control_str_config_t;


/*
*   -Description-
*   This function is used to set the clock system configuration.
*
*   -Input parameters-
*   - ptr_str_sys_control_config: Pointer to a structure containing the clock system configuration (sys_control_str_config_t*).
*
*   -Implementation-
*   The function clears the USERCC2 bit in the SYS_CONTROL_RCC2 register.
*   It then checks if the prescaler value in the configuration structure is greater than 1. If true, it sets the USESYSDIV bit in the SYS_CONTROL_RCC register and updates the SYSDIV field with the prescaler value.
*   Otherwise, it clears the USESYSDIV bit.
*   The function sets the BYPASS bit in the SYS_CONTROL_RCC register and updates the OSCSRC field with the oscillator source value from the configuration structure.
*   Finally, it sets the PWRDN bit in the SYS_CONTROL_RCC register.
*   Note: The actual register addresses and bit manipulation are not shown in this code snippet.
*/

void sys_control_set_clock_system(sys_control_str_config_t *ptr_str_sys_control_config);
#endif
