#ifndef CAR_MANAGER_CTR_H
#define CAR_MANAGER_CTR_H

#include "motor_interface.h"

typedef enum    {
    CAR_STOP = 0,
    CAR_FORWARD,
    CAR_BACKWARD,
    CAR_RIGHT,
    CAR_LEFT
}enm_car_direction_t;


typedef struct{
    str_motor_config_t motor_1_config;
    str_motor_config_t motor_2_config;
    // if there is any additional configuration or sensors wrote it here
}str_car_config_t;

typedef enum 
{
    CAR_OK,
    CAR_NOK,
} enm_car_error_t;

/************************************************************************
 *description : used to initlize the two motor as output
 *input       : this function take two pointers to motor structure
 *return      : MOTOR_OK, MOTOR_NOK
 ************************************************************************/
enm_car_error_t car_init(const str_car_config_t *car_config);

/************************************************************************
 *description : used to move the car  by specific direction
 *input       : this function take two pointers to motor structure and speed of the car
 *return      : MOTOR_OK, MOTOR_NOK
 ************************************************************************/
enm_car_error_t car_move(const str_car_config_t *car_config, enm_car_direction_t enm_car_direction);

/************************************************************************
 *description : used to stop the car
 *input       : this function take two pointers to motor structure
 *return      : MOTOR_OK, MOTOR_NOK
 ************************************************************************/
enm_car_error_t car_stop(const str_car_config_t *car_config);

#endif //CAR_MANAGER_CTR_H
