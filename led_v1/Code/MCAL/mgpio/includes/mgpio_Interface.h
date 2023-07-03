 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 14 - 6 - 2023
 *  Description 			: MGPIO_Interface.h --> Function Prototypes
 *  Module Features		:
 *  											01- MGPIO_u8Init()
 *  											02- MGPIO_u8SetPinData()
													03-	MGPIO_u8GetPinData()
													04-	MGPIO_u8IRQEnable()
													05-	MGPIO_vidIRQDisable()
													06-	MGPIO_u8SetCallBack()
 *****************************************************************************/

/*********************************************************************************************************
 *  										Header Guard Of File
 ********************************************************************************************************/
#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

/********************************************************************************************************************
*												Standard Types LIB
********************************************************************************************************************/
#include "LSTD_TYPES.h"
#include "TM4C123.h"
/*********************************************************************************************************
 *  										MACROS
 ********************************************************************************************************/
 
 /***********************  Error Status    **************************/
/*---------------------------------------------------------------*/
 #define MGPIO_SUCCESS				1
 #define MGPIO_FAILED					0
 
 
/***********************  PORT SEL    **************************/
/*---------------------------------------------------------------*/
#define MGPIO_PORTA					0
#define MGPIO_PORTB					1
#define MGPIO_PORTC					2
#define MGPIO_PORTD					3
#define MGPIO_PORTE					4
#define MGPIO_PORTF					5


/***********************   Pull Type    **************************/
/*---------------------------------------------------------------*/
#define MGPIO_NO_PULL				0
#define MGPIO_PULL_UP				1
#define MGPIO_PULL_DOWN			2
#define MGPIO_PULL_TYPE_MAX 3


/***********************  Pin Value    **************************/
/*---------------------------------------------------------------*/
#define MGPIO_PIN_LOW			0
#define MGPIO_PIN_HIGH		1
#define MGPIO_PIN_TOG			2
#define MGPIO_PIN_MAX			3

/*********************************************************************************************************
 *  									User Defined Data Type
 ********************************************************************************************************/

/***********************   Pin Selection    **************************/
typedef enum
{
	MGPIO_PINA_0 = 0,
	MGPIO_PINA_1,
	MGPIO_PINA_2,
	MGPIO_PINA_3,
	MGPIO_PINA_4,
	MGPIO_PINA_5,
	MGPIO_PINA_6,
	MGPIO_PINA_7,

						
	MGPIO_PINB_0,
	MGPIO_PINB_1,
	MGPIO_PINB_2,
	MGPIO_PINB_3,
	MGPIO_PINB_4,
	MGPIO_PINB_5,
	MGPIO_PINB_6,
	MGPIO_PINB_7,

						
	MGPIO_PINC_0,
	MGPIO_PINC_1,
	MGPIO_PINC_2,
	MGPIO_PINC_3,
	MGPIO_PINC_4,
	MGPIO_PINC_5,
	MGPIO_PINC_6,
	MGPIO_PINC_7,

						
	MGPIO_PIND_0,
	MGPIO_PIND_1,
	MGPIO_PIND_2,
	MGPIO_PIND_3,
	MGPIO_PIND_4,
	MGPIO_PIND_5,
	MGPIO_PIND_6,
	MGPIO_PIND_7,

						
	MGPIO_PINE_0,
	MGPIO_PINE_1,
	MGPIO_PINE_2,
	MGPIO_PINE_3,
	MGPIO_PINE_4,
	MGPIO_PINE_5,
	MGPIO_PINE_6,
	MGPIO_PINE_7,

						
	MGPIO_PINF_0,
	MGPIO_PINF_1,
	MGPIO_PINF_2,
	MGPIO_PINF_3,
	MGPIO_PINF_4,
	MGPIO_PINF_5,
	MGPIO_PINF_6,
	MGPIO_PINF_7,

	
	
	MGPIO_PIN_INVALID

}enu_pin_t;


/***********************   Pin Mode Selection    **************************/
typedef enum
{
	MGPIO_MODE_DIGITAL=0,
	MGPIO_MODE_ALTF,
	MGPIO_MODE_ANALOG,
	
	MGPIO_MODE_INVALID

}enu_gpio_mode_t;


typedef enum
{
	MGPIO_DIR_INPUT=0,
	MGPIO_DIR_OUTPUT,
	MGPIO_DIR_INVALID
}enu_pin_dir_mode_t;

/***********************  Pin current Selection    **************************/
typedef enum
{
	MGPIO_OPEN_DRAIN=0,
	MGPIO_MAMP_2,
	MGPIO_MAMP_4,
	MGPIO_MAMP_8,

	MGPIO_MAMP_INVALID

}enu_gpio_amp_mode_t;


/* Interrupt Configuration Selection */
/*-----------------------------------*/
typedef enum
{
	MGPIO_INT_ENABLE=0,
	MGPIO_INT_DISABLE,
	
	MGPIO_INT_INVALID
	
}enu_gpio_int_t;


typedef enum
{
	MGPIO_INT_EDGE_SENSETIVE=0,
	MGPIO_INT_LEVEL_SENSETIVE,
	
	MGPIO_INT_SENSE_TYPE_INVALID
	
}enu_int_sens_type_t;


typedef enum
{
	MGPIO_INT_BOTH_EDGES=0,
	MGPIO_INT_FALL_E_LOW_L,
	MGPIO_INT_RIS_E_HIGH_L,
	
	MGPIO_INT_SENS_CTRL_INVALID
	
}enu_int_sens_ctrl_t;


/* GPIO configuration done by user*/
/*-----------------------------------*/
typedef struct
{
	enu_pin_t 						enu_pin;
	enu_gpio_mode_t 			enu_gpio_mode;
	enu_pin_dir_mode_t		enu_pin_dir_mode;
	union
	{
		enu_gpio_amp_mode_t		enu_gpio_amp_mode;
		uint8_								u8_input_pull_type;
	}un_gpio_conf;

} st_gpio_cfg_t ;




/********************************************************************************************************************
 *  										Function ProtoType
*******************************************************************************************************************/

/*****************************************************************************************************************
*											01- MGPIO_u8Init()									
* ----------------------------------------------------------------------------------
 * @func  : Pin Mode configuration
 * @in[1] : Address of struct Instance
 * @out    : uint8_  [eroor status if execute well return {MGPIO_SUCCESS} if not return {MGPIO_FAILED}]
 ******************************************************************************************************************/
uint8_ MGPIO_u8Init(st_gpio_cfg_t* st_gpio_cfg);

/***********************************************************************************/
/*			02- MGPIO_u8SetPinData()									*/
/* ----------------------------------------------------------------------------------
 * @func  : Set output pin to low or high
 * @in[1] : Copy_enPinNum
 * 				- MGPIO_PINA_0 ~ MGPIO_PINF_7
 *
 * @in[2]  : Copy_PinValue  :
 * 				- MGPIO_PIN_LOW
 * 				- MGPIO_PIN_HIGH
 * @out    : uint8_  [eroor status if execute well return {MGPIO_SUCCESS} if not return {MGPIO_FAILED}]
 ************************************************************************************/
uint8_ MGPIO_u8SetPinData		(enu_pin_t Copy_enPinNum, uint8_ Copy_PinValue);

/***********************************************************************************/
/*			03- MGPIO_u8GetPinData()									*/
/* ----------------------------------------------------------------------------------
 * @func  : Get pin Value
 * @in[1] : Copy_enPinNum
 * 				- MGPIO_PINA_0 ~ MGPIO_PINF_7
 *
 * @in[2]  : Ref_puint8_PinVal  : Reference to variable where the value status store on it
 * @out    : uint8_  [eroor status if execute well return {MGPIO_SUCCESS} if not return {MGPIO_FAILED}]
 ************************************************************************************/
uint8_ MGPIO_u8GetPinData		(enu_pin_t Copy_enPinNum , uint8_* Ref_puint8_PinVal);


/***************************************************************************************************************/
/*																			04- MGPIO_u8IRQEnable()									*/
/* ----------------------------------------------------------------------------------------------------------
 * @func  : Interrupt Enable
 * @in[1] : Copy_enPinNum
 * 				- MGPIO_PINA_0 ~ MGPIO_PINF_7
 *
 * @in[2] : enu_int_sens_type
 *				- MGPIO_INT_EDGE_SENSETIVE ~ MGPIO_INT_LEVEL_SENSETIVE
 * #in[3]	: enu_int_sens_ctrl
 *				- MGPIO_INT_BOTH_EDGES - MGPIO_INT_FALL_E_LOW_L - MGPIO_INT_RIS_E_HIGH_L
 * @out    : uint8_  [eroor status if execute well return {MGPIO_SUCCESS} if not return {MGPIO_FAILED}]
 ****************************************************************************************************************/
uint8_ MGPIO_u8IRQEnable(enu_pin_t Copy_enPinNum, enu_int_sens_type_t enu_int_sens_type, enu_int_sens_ctrl_t enu_int_sens_ctrl);



/***************************************************************************************************************/
/*																			05- MGPIO_vidIRQDisable()									*/
/* ----------------------------------------------------------------------------------------------------------
 * @func  : Interrupt Enable
 * @in[1] : Copy_enPinNum
 * 				- MGPIO_PINA_0 ~ MGPIO_PINF_7
 * @out    : uint8_  [eroor status if execute well return {MGPIO_SUCCESS} if not return {MGPIO_FAILED}]
 ****************************************************************************************************************/
uint8_ MGPIO_u8IRQDisable(enu_pin_t Copy_enPinNum);


/***************************************************************************************************************/
/*																			06- MGPIO_u8SetCallBack()									*/
/* ----------------------------------------------------------------------------------------------------------
 * @func  : Set Call back function
 * @in[1] : Copy_enPinNum
 * 				- MGPIO_PINA_0 ~ MGPIO_PINF_7
 * @in[2] : ptr_func
 *				- Address of application Function
 * @out    : uint8_  [eroor status if execute well return {MGPIO_SUCCESS} if not return {MGPIO_FAILED}]
 ****************************************************************************************************************/
uint8_ MGPIO_u8SetCallBack(enu_pin_t Copy_enPinNum, ptr_func_t ptr_func);


#endif /* MGPIO_INTERFACE_H_ */
