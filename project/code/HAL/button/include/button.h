/*
 *		File		: button.h
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: Button functions Prototypes
 */
/************************************************************************************************
*											File Guard
************************************************************************************************/
#ifndef HAL_BUTTON_BUTTON_H_
#define HAL_BUTTON_BUTTON_H_
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/EXIT/EXIT_interface.h"
#include "../../COM/std_types.h"
#include "../../COM/bit_math.h"
/***********************************************************************************************
*										User defined data type
***********************************************************************************************/
typedef enum {
    BUTTON_RELEASED=0,
    BUTTON_PRESSED

}btn_enu_btn_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW=0,
    BUTTON_ACTIVE_HIGH
}btn_enu__btn_active_t;

typedef struct{
    dio_enu_portx_t port_name;
    dio_enu_pinx_t pin;
    btn_enu_btn_state_t button_state;
    btn_enu__btn_active_t button_active;
}button_str_btn_config_t;


typedef enum
{
	BTN_NOT_OK=0,
    BTN_OK,
    BTN_NULL_PTR

}enu_buttonError_t;


/***********************************************************************************************
*										Functions Prototype
***********************************************************************************************/
enu_buttonError_t HButton_Init(button_str_btn_config_t * en_pinx);
enu_buttonError_t HButton_getPinVal(button_str_btn_config_t *en_pinx,  btn_enu_btn_state_t* enu_refVal );
enu_buttonError_t HButton_initializa_with_int(const button_str_btn_config_t* ptr_str_btn_config , ptr_func_t ptr_callback);
enu_buttonError_t HButton_enable_INT( button_str_btn_config_t* ptr_str_btn_config);
enu_buttonError_t HButton_disable_INT( button_str_btn_config_t* ptr_str_btn_config);

#endif /* HAL_BUTTON_BUTTON_H_ */
/***********************************************************************************************
*										END
***********************************************************************************************/
