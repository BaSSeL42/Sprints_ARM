

#include "motor_interface.h"
#include "DIO_interface.h"

enm_motor_error_t motor_init( str_motor_config_t *str_motor_config){
    // check if pointer is null 
    if (str_motor_config == NULL) return MOTOR_NOK;    

    // init the motor DIO pins
    dio_enu_return_state_t l_str_dio_error_status;
    dio_str_pin_Config_t motor_temp_pin1_conf = {
        .enu_pin = str_motor_config->pin_1,
        .enu_pin_mode = DIO_PIN_OUTPUT,
        .enu_port = str_motor_config->port_name,
        .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state =  DIO_PIN_LOW_STATE,
        };
    dio_str_pin_Config_t motor_temp_pin2_conf = {
        .enu_pin = str_motor_config->pin_2,
        .enu_pin_mode = DIO_PIN_OUTPUT,
        .enu_port = str_motor_config->port_name,
        .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE,
    };
    l_str_dio_error_status = dio_init_pin(&motor_temp_pin1_conf);
    if (l_str_dio_error_status != DIO_OK) return MOTOR_NOK;
    
    l_str_dio_error_status = dio_init_pin(&motor_temp_pin2_conf);
    if (l_str_dio_error_status != DIO_OK) return MOTOR_NOK;

    // enable clock source 

    l_str_dio_error_status = dio_enable_clock(str_motor_config->port_name);
    if (l_str_dio_error_status != DIO_OK) return MOTOR_NOK;

    return MOTOR_OK;
}

enm_motor_error_t motor_move( str_motor_config_t *str_motor_config, enm_motor_dir_t enm_motor_dir)
{
    // check if pointer is null
    if (str_motor_config == NULL)
        return MOTOR_NOK;

    // init the motor DIO pins
    dio_enu_return_state_t l_str_dio_error_status;
    dio_str_pin_Config_t motor_temp_pin1_conf = {
        .enu_pin = str_motor_config->pin_1,
        .enu_pin_mode = DIO_PIN_OUTPUT,
        .enu_port = str_motor_config->port_name,
        .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE,
    };
    dio_str_pin_Config_t motor_temp_pin2_conf = {
        .enu_pin = str_motor_config->pin_2,
        .enu_pin_mode = DIO_PIN_OUTPUT,
        .enu_port = str_motor_config->port_name,
        .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE,
    };
    switch (enm_motor_dir)
    {
    case MOTOR_FORWARD:
        l_str_dio_error_status = dio_set_pin(&motor_temp_pin1_conf, DIO_PIN_HIGH_STATE);
        l_str_dio_error_status = dio_set_pin(&motor_temp_pin2_conf, DIO_PIN_LOW_STATE);
        break;
    case MOTOR_BACKWARD:
        l_str_dio_error_status = dio_set_pin(&motor_temp_pin1_conf, DIO_PIN_LOW_STATE);
        l_str_dio_error_status = dio_set_pin(&motor_temp_pin2_conf, DIO_PIN_HIGH_STATE);
        break;
    default:
        return MOTOR_NOK;
        break;
    }
    l_str_dio_error_status = dio_enable_clock(str_motor_config->port_name);
    if (l_str_dio_error_status != DIO_OK)
        return MOTOR_NOK;

    return MOTOR_OK;
}

enm_motor_error_t motor_stop( str_motor_config_t* str_motor_config){
    // check if pointer is null
    if (str_motor_config == NULL)
        return MOTOR_NOK;

    // init the motor DIO pins
    dio_enu_return_state_t l_str_dio_error_status;
    dio_str_pin_Config_t motor_temp_pin1_conf = {
        .enu_pin = str_motor_config->pin_1,
        .enu_pin_mode = DIO_PIN_OUTPUT,
        .enu_port = str_motor_config->port_name,
        .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE,
    };
    dio_str_pin_Config_t motor_temp_pin2_conf = {
        .enu_pin = str_motor_config->pin_2,
        .enu_pin_mode = DIO_PIN_OUTPUT,
        .enu_port = str_motor_config->port_name,
        .un_input_output_type.str_output_type_and_speed_and_state.enu_pin_state = DIO_PIN_LOW_STATE,
    };
    l_str_dio_error_status = dio_set_pin(&motor_temp_pin1_conf, DIO_PIN_LOW_STATE);
    l_str_dio_error_status = dio_set_pin(&motor_temp_pin2_conf, DIO_PIN_LOW_STATE);
    if (l_str_dio_error_status != DIO_OK)
        return MOTOR_NOK;

    return MOTOR_OK;
}
