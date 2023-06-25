#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


#include "../../COM/bit_math.h"
#include "../../COM/std_types.h"

typedef enum{
    DIO_PORTA=0,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PORTD,
    DIO_PORTE,
    DIO_PORTF,
		MAX_INVALID_PORT
}dio_enu_portx_t;

typedef enum{
    DIO_PIN_0=0,
    DIO_PIN_1,
    DIO_PIN_2,
    DIO_PIN_3,
    DIO_PIN_4,
    DIO_PIN_5,
    DIO_PIN_6,
    DIO_PIN_7,
		MAX_INVALID_PIN
}dio_enu_pinx_t;

typedef enum{
    DIO_PIN_LOW_STATE=0,
    DIO_PIN_HIGH_STATE
}dio_enu_pin_state_t;


typedef enum{
    DIO_PIN_INPUT=0,
    DIO_PIN_OUTPUT,
    DIO_PIN_AFM,
    DIO_PIN_ANALOG
}dio_enu_pin_mode_t;

typedef enum{
    DIO_PIN_OUTPUT_PUSH_PULL=0,
    DIO_PIN_OUTPUT_OPEN_DRAIN,

}dio_enu_output_type_t;

typedef enum{
    DIO_PIN_2MA=0,
    DIO_PIN_4MA,
    DIO_PIN_8MA
}dio_enu_output_current_t;

typedef struct 
{
    dio_enu_output_type_t   	enu_output_type;
		dio_enu_output_current_t	enu_output_current;
    dio_enu_pin_state_t     	enu_pin_state;

}dio_str_output_type_and_speed_and_state_t;



typedef enum{
    DIO_PIN_INPUT_NO_PULL_UP_NO_PULL_DOWN=0,
    DIO_PIN_INPUT_PULL_UP,
    DIO_PIN_INPUT_PULL_DOWN
}dio_enu_input_type_t;


typedef union 
{
    dio_str_output_type_and_speed_and_state_t str_output_type_and_speed_and_state;
    dio_enu_input_type_t enu_input_type;
    
}dio_un_input_output_type_t;


typedef struct
{
    dio_enu_portx_t enu_port;
    dio_enu_pinx_t enu_pin;
    dio_enu_pin_mode_t enu_pin_mode;
    dio_un_input_output_type_t un_input_output_type;
}dio_str_pin_Config_t;


typedef enum{
    DIO_NOT_OK=0,
    DIO_OK,
    DIO_NULL_PTR,
    DIO_EXCEED_PORT
}dio_enu_return_state_t;

dio_enu_return_state_t  dio_enable_clock(dio_enu_portx_t copy_enu_port_num);
dio_enu_return_state_t  dio_init_pin(dio_str_pin_Config_t *ptr_str_pinconfig);
dio_enu_return_state_t  dio_set_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t copy_enu_pin_state);
dio_enu_return_state_t  dio_toggle_pin(dio_str_pin_Config_t *ptr_str_pinconfig);
dio_enu_return_state_t  dio_read_pin(dio_str_pin_Config_t *ptr_str_pinconfig, dio_enu_pin_state_t *ptr_enu_pin_state);
dio_enu_return_state_t  dio_unlock_special_pin(dio_str_pin_Config_t *ptr_str_pinconfig);
#endif