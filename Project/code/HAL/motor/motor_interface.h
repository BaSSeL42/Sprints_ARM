

#ifndef		MOTOR_HAL
#define 	MOTOR_HAL

#include "DIO_interface.h"

typedef enum {
	MOTOR_FORWARD,
	MOTOR_BACKWARD
}enm_motor_dir_t;

typedef enum  
{ 
	MOTOR_OK,
    MOTOR_NOK
}enm_motor_error_t;

typedef struct
{
	dio_enu_portx_t port_name;
	dio_enu_pinx_t pin_1 , pin_2;
}str_motor_config_t;

/*************************************************************APIs prototypes*******************************************************************/



/************************************************************************
* description : this function used to init the motor as output
* input       : pointer to str_motor_config_t structure
* return      :MOTOR_OK or MOTR_NOK                                                                     
************************************************************************/
enm_motor_error_t motor_init( str_motor_config_t* str_motor_config);


/************************************************************************
* description : this function used to move the motor 
* input       : pointer to str_motor_config_t structure  and the direction of the movment enum 
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
enm_motor_error_t motor_move( str_motor_config_t* str_motor_config,enm_motor_dir_t enm_motor_dir);



/************************************************************************
* description : this function used to stop the motor
* input       : pointer to str_motor_config_t structure
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
enm_motor_error_t motor_stop( str_motor_config_t* str_motor_config);


#endif
