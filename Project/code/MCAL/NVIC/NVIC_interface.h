#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#include "../../COM/bit_math.h"
#include "../../COM/std_types.h"
typedef enum {
	GPIO_A=0,
	GPIO_B,
	GPIO_C,
	GPIO_D,
	GPIO_E,
	UART_0,
	UART_1,
	SSI_0,
	I_2C_0,
	PWM0_Fault,
	PWM0_Generator_0,
	PWM0_Generator_1,
	PWM0_Generator_2,
	QEI_0,
	ADC0_Sequence_0,
	ADC0_Sequence_1,
	ADC0_Sequence_2,
	ADC0_Sequence_3,
	Watchdog_Timers_0_1,
	Timer_0_A,
	Timer_0_B,
	Timer_1_A,
	Timer_1_B,
	Timer_2_A,
	Timer_2_B,
	Analog_Comparator_0,
	Analog_Comparator_1,
	GPIO_F = 30,
	NVIC_MAX_INVALID_INT
}nvic_enu_interupt_index_t ;


typedef enum{
    NVIC_NOT_OK=0,
    NVIC_OK,
    NVIC_NULL_PTR,
    NVIC_MAX_INVALID_LOAD_VALUE
}nvic_enu_return_state_t;


/*
*   -Description-
*   This function is used to enable a specific peripheral interrupt source in the NVIC.
*
*   -Input parameters-
*   - copy_enu_interupt_index: The interrupt index to be enabled (nvic_enu_interupt_index_t).
*
*   -Return-
*   -Return cases-
*   - NVIC_NOT_OK: An error occurred.
*   - NVIC_OK: The operation was successful.
*
*   -Implementation-
*   The function checks the value of copy_enu_interupt_index and sets the corresponding bit in the NVIC_ENx register based on the range of the interrupt index.
*   The return value is initialized as NVIC_NOT_OK by default.
*   Note: The actual implementation inside the if-else statements is not shown in this code snippet.
*/
nvic_enu_return_state_t nvic_EnablePeripheral  ( nvic_enu_interupt_index_t copy_enu_interupt_index);



/*
*   -Description-
*   This function is used to disable a specific peripheral interrupt source in the NVIC.
*
*   -Input parameters-
*   - copy_enu_interupt_index: The interrupt index to be disabled (nvic_enu_interupt_index_t).
*
*   -Return-
*   -Return cases-
*   - NVIC_NOT_OK: An error occurred.
*   - NVIC_OK: The operation was successful.
*
*   -Implementation-
*   The function checks the value of copy_enu_interupt_index and sets the corresponding bit in the NVIC_DISx register based on the range of the interrupt index.
*   The return value is initialized as NVIC_NOT_OK by default.
*   Note: The actual implementation inside the if-else statements is not shown in this code snippet.
*/
nvic_enu_return_state_t nvic_DisablePeripheral ( nvic_enu_interupt_index_t copy_enu_interupt_index );





#endif