#ifndef EXIT_INTERFACE_H
#define EXIT_INTERFACE_H

#include "../DIO/DIO_interface.h"
#include "../NVIC/NVIC_interface.h"
#include "../../COM/bit_math.h"
#include "../../COM/std_types.h"


typedef enum{
    EXIT_PULL_UP=0,
    EXIT_PULL_DOWN,
    EXIT_OPEN_DRAIN
}exit_enu_idle_mode_t;

typedef enum{
    EXIT_RISING_EDGE=0,
    EXIT_FALLING_EDGE,
    EXIT_BOTH_EDGE
}exit_enu_trigger_mode_t;

typedef struct{
	dio_enu_portx_t enu_port;
  dio_enu_pinx_t enu_pin;
}exit_special_pin;

typedef struct
{
    dio_enu_portx_t enu_port;
    dio_enu_pinx_t enu_pin;
		exit_enu_trigger_mode_t enu_trigger_mode;
    exit_enu_idle_mode_t enu_idle_state;
}exit_str_pin_Config_t;


typedef enum{
    EXIT_NOT_OK=0,
    EXIT_OK,
    EXIT_NULL_PTR,
    EXIT_EXCEED_PORT
}exit_enu_return_state_t;

exit_enu_return_state_t  exit_init_pin(exit_str_pin_Config_t *ptr_str_pin_config);
exit_enu_return_state_t  exit_enable_int(exit_str_pin_Config_t *ptr_str_pin_config);
exit_enu_return_state_t  exit_disable_int(exit_str_pin_Config_t *ptr_str_pin_config);
exit_enu_return_state_t  exit_set_callback(exit_str_pin_Config_t *ptr_str_pin_config, ptr_vfunc ptr_call_back);
#endif