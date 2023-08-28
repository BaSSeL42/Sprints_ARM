#include "car_control_interface.h"


enm_car_error_t car_init(const str_car_config_t *car_config)
{
    // check if car pointer is null
    if( car_config == NULL){
        return CAR_NOK;
    }
    enm_motor_error_t enm_motor_error;
    // motor init
    enm_motor_error = motor_init((str_motor_config_t *)&(car_config->motor_1_config));
    enm_motor_error = motor_init((str_motor_config_t *)&(car_config->motor_2_config));

    if (enm_motor_error != MOTOR_OK)
        return CAR_NOK;
    return CAR_OK;
}

enm_car_error_t car_move(const str_car_config_t *car_config, enm_car_direction_t enm_car_direction)
{
    // check if car pointer is null
    if( car_config == NULL){
        return CAR_NOK;
    }
    enm_motor_error_t enm_motor_error;
    switch (enm_car_direction)
    {
    case CAR_STOP:
        
        enm_motor_error = motor_stop((str_motor_config_t *)&(car_config->motor_1_config));
        enm_motor_error = motor_stop((str_motor_config_t *)&(car_config->motor_2_config));
        break;
    case CAR_FORWARD:
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_1_config), MOTOR_FORWARD);
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_2_config), MOTOR_FORWARD);
        
        break;
    case CAR_BACKWARD:
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_1_config), MOTOR_BACKWARD);
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_2_config), MOTOR_BACKWARD);
        
        break;
    case CAR_RIGHT:
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_1_config), MOTOR_FORWARD);
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_2_config), MOTOR_BACKWARD);
        break;
    case CAR_LEFT:
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_1_config), MOTOR_BACKWARD);
        enm_motor_error = motor_move((str_motor_config_t *)&(car_config->motor_2_config), MOTOR_FORWARD);
        break;

    default:
        return CAR_NOK;
        break;
    }

    if (enm_motor_error != MOTOR_OK)
        return CAR_NOK;
    return CAR_OK;
}

enm_car_error_t car_stop(const str_car_config_t *car_config){
    // check if car pointer is null
    if( car_config == NULL){
        return CAR_NOK;
    }
    enm_motor_error_t enm_motor_error;
    enm_motor_error = motor_stop((str_motor_config_t *)&(car_config->motor_1_config));
    enm_motor_error = motor_stop((str_motor_config_t *)&(car_config->motor_2_config));
    if (enm_motor_error != MOTOR_OK)
        return CAR_NOK;
    return CAR_OK;
}
