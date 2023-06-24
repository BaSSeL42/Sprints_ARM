 /**************************************************************
 *  AUTHOR 						: Bassel Yasser
 *  Version 					: V0.0.0
 *  Date							: 13 - 6 - 2023
 *  Description 			: MGPIO_Interface.h --> Function Prototypes
 *  Module Features		:
 *  											01- MGPIO_u8Init()
 *  											02- MGPIO_u8SetPinData()
													03-	MGPIO_u8GetPinData()
													04-	MGPIO_u8IRQEnable()
													05-	MGPIO_vidIRQDisable()
													06-	MGPIO_u8SetCallBack()
 *****************************************************************************/

/********************************************************************************************************************
*												Standard Types LIB
********************************************************************************************************************/
//#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
/********************************************************************************************************************
*												Peripheral Files
********************************************************************************************************************/
#include "mgpio_Private.h"
#include "mgpio_Interface.h"
#include "mgpio_Config.h"
/********************************************************************************************************************
*												Global Variables
********************************************************************************************************************/

static ptr_func_t gl_a_ptr_func[6] = {NULL,NULL,NULL,NULL,NULL,NULL};

/********************************************************************************************************************
 *  										Function Implementation
*******************************************************************************************************************/
uint8_ MGPIO_u8Init(st_gpio_cfg_t* st_gpio_cfg)
{
	uint8_ loc_u8_error_status  = MGPIO_SUCCESS;

	uint8_ loc_u8_PortNum;
	uint8_ loc_u8_PinNum;

	if (st_gpio_cfg != NULL)
	{
		if (st_gpio_cfg->enu_pin 						< MGPIO_PIN_INVALID			&&
				st_gpio_cfg->enu_gpio_mode 			< MGPIO_MODE_INVALID		&&
				st_gpio_cfg->enu_pin_dir_mode 	< MGPIO_DIR_INVALID			&&
				((st_gpio_cfg->un_gpio_conf.enu_gpio_amp_mode 	< MGPIO_MAMP_INVALID) || (st_gpio_cfg->un_gpio_conf.u8_input_pull_type < MGPIO_PULL_TYPE_MAX))    )
		{
			loc_u8_PortNum 	= st_gpio_cfg->enu_pin / 8;
			loc_u8_PinNum		= st_gpio_cfg->enu_pin % 8;
			
			
			
		}
		else
		{
			loc_u8_error_status = MGPIO_FAILED;
		}

	}
	else
	{
		loc_u8_error_status = MGPIO_FAILED;
	}
	return loc_u8_error_status;
}



/********************************************************************************************************************/
uint8_ MGPIO_u8SetPinData(enu_pin_t Copy_enPinNum, uint8_ Copy_PinValue)
{
	uint8_ loc_u8_error_status  = MGPIO_SUCCESS;
	uint8_ loc_u8_PortNum;
	uint8_ loc_u8_PinNum;
	
	if(Copy_enPinNum < MGPIO_PIN_INVALID && Copy_PinValue < MGPIO_PIN_MAX)
	{
		loc_u8_PortNum = Copy_enPinNum / 8;
		loc_u8_PinNum = Copy_enPinNum % 8;


	}else
	{
	loc_u8_error_status  = MGPIO_FAILED;
	}
	return loc_u8_error_status;
}
/********************************************************************************************************************/
uint8_ MGPIO_u8GetPinData(enu_pin_t Copy_enPinNum , uint8_* Ref_puint8_PinVal)
{
	uint8_ loc_u8_error_status  = MGPIO_SUCCESS;
	uint8_ loc_u8_PortNum;
	uint8_ loc_u8_PinNum;
	
	if(Copy_enPinNum < MGPIO_PIN_INVALID && Ref_puint8_PinVal != NULL)
	{
		loc_u8_PortNum = Copy_enPinNum / 8;
		loc_u8_PinNum = Copy_enPinNum % 8;

	}else
	{
	loc_u8_error_status  = MGPIO_FAILED;
	}

	return loc_u8_error_status;
}
/********************************************************************************************************************/
uint8_ MGPIO_u8IRQEnable(enu_pin_t Copy_enPinNum, enu_int_sens_type_t enu_int_sens_type, enu_int_sens_ctrl_t enu_int_sens_ctrl)
{
	uint8_ loc_u8_error_status  = MGPIO_SUCCESS;
	uint8_ loc_u8_PortNum;
	uint8_ loc_u8_PinNum;
	if(enu_int_sens_type < MGPIO_INT_SENSE_TYPE_INVALID && 
		enu_int_sens_ctrl < MGPIO_INT_SENS_CTRL_INVALID		&&
		Copy_enPinNum < MGPIO_PIN_INVALID)
	{
		loc_u8_PortNum = Copy_enPinNum / 8;
		loc_u8_PinNum = Copy_enPinNum % 8;	
		

	}
	else
	{
			loc_u8_error_status  = MGPIO_FAILED;
	}

	return loc_u8_error_status;	
}



/********************************************************************************************************************/
uint8_ MGPIO_u8IRQDisable(enu_pin_t Copy_enPinNum)
{
	uint8_ loc_u8_error_status  = MGPIO_SUCCESS;
	uint8_ loc_u8_PortNum;
	uint8_ loc_u8_PinNum;
	
	if(Copy_enPinNum < MGPIO_PIN_INVALID)
	{

	}
	
	else
	{
	loc_u8_error_status  = MGPIO_FAILED;
	}

	return loc_u8_error_status;	
}


/********************************************************************************************************************/
/********************************************************************************************************************/

uint8_ MGPIO_u8SetCallBack(enu_pin_t Copy_enPinNum, ptr_func_t ptr_func)
{
	uint8_ loc_u8_error_status  = MGPIO_SUCCESS;
	uint8_ loc_u8_PortNum;
	
	if(Copy_enPinNum < MGPIO_PIN_INVALID && ptr_func != NULL)
	{

	}
	
	else
	{
	loc_u8_error_status  = MGPIO_FAILED;
	}

	return loc_u8_error_status;		
	
}



/********************************************************************************************************************/
/************************************    Interrupt Handler   ********************************************************/
/********************************************************************************************************************/
void GPIOA_Handler(void)
{
	
	if ( gl_a_ptr_func[MGPIO_PORTA] != NULL )
		{
			gl_a_ptr_func[MGPIO_PORTA]();
		}
}

void GPIOB_Handler(void)
{
	if ( gl_a_ptr_func[MGPIO_PORTB] != NULL )
		{
			gl_a_ptr_func[MGPIO_PORTB]();
		}
}

void GPIOC_Handler(void)
{
	if ( gl_a_ptr_func[MGPIO_PORTC] != NULL )
		{
			gl_a_ptr_func[MGPIO_PORTC]();
		}
}

void GPIOD_Handler(void)
{
	if ( gl_a_ptr_func[MGPIO_PORTD] != NULL )
		{
			gl_a_ptr_func[MGPIO_PORTD]();
		}
}

void GPIOE_Handler(void)
{
	if ( gl_a_ptr_func[MGPIO_PORTE] != NULL )
		{
			gl_a_ptr_func[MGPIO_PORTE]();
		}
}

void GPIOF_Handler(void)
{
	if ( gl_a_ptr_func[MGPIO_PORTF] != NULL )
		{
			gl_a_ptr_func[MGPIO_PORTF]();
		}
}



