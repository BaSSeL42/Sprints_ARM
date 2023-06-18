 /**************************************************************
 *  AUTHOR 				: Bassel Yasser
 *  Version 			: V0.0.0
 *  Date				: 4 - 2 - 2023
 *  Description 		: MGPIO_Private.h --> Register Description
 *****************************************************************************/


/********************************************************************************************************************
*												File Guard
********************************************************************************************************************/
#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_


#define GPIO_APB 		0
#define GPIO_AHB		1
#define GPIO_BUS_TYPE		GPIO_APB

#if GPIO_BUS_TYPE == GPIO_APB
/********************************************************************************************************************
*												MACROS
********************************************************************************************************************/
#define MGPIO_OFFSET(X)		( ((X) < 4)? ( (0x40004000) + ( (X)*(0x1000) ) ):( (0x40024000) + ( ((X)-4)*(0x1000) ) ) )

//MGPIO_A_BASE_ADDRESS				0x40004000
//MGPIO_B_BASE_ADDRESS				0x40005000
//MGPIO_C_BASE_ADDRESS				0x40006000
//MGPIO_D_BASE_ADDRESS				0x40007000
//MGPIO_E_BASE_ADDRESS				0x40024000
//MGPIO_F_BASE_ADDRESS				0x40025000


#elif  GPIO_BUS_TYPE == GPIO_AHB


#error " AHB is not supported yet"

#else 


#endif




/********************************************************************************************************************
*												Register Definition
********************************************************************************************************************/
#define GPIODATA(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x3FC )))
#define GPIODIR(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x400 )))
#define GPIOIS(x)						(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x404 )))
#define GPIOIBE(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x408 )))
#define GPIOIEV(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x40C )))
#define GPIOIM(x)						(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x410 )))
#define GPIORIS(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x414 )))
#define GPIOMIS(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x418 )))
#define GPIOICR(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x41C )))
#define GPIOAFSEL(x)				(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x420 )))
#define GPIODR2R(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x500 )))
#define GPIODR4R(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x504 )))
	
#define GPIODR8R(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x508 )))
#define GPIOODR(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x50C )))	
#define GPIOPUR(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x510 )))
#define GPIOPDR(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x514 )))
#define GPIOSLR(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x518 )))	
#define GPIODEN(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x51C )))
#define GPIOLOCK(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x520 )))
#define GPIOCR(x)						(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x524 )))
#define GPIOAMSEL(x)				(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x528 )))
#define GPIOPCTL(x)					(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x52C )))
	
#define GPIOADCCTL(x)				(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x530 )))
#define GPIODMACTL(x)				(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0x534 )))
#define GPIOPeriphID4(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFD0 )))
#define GPIOPeriphID5(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFD4 )))
#define GPIOPeriphID6(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFD8 )))
#define GPIOPeriphID7(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFDC )))
#define GPIOPeriphID0(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFE0 )))
#define GPIOPeriphID1(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFE4 )))
#define GPIOPeriphID2(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFE8 )))
#define GPIOPeriphID3(x)		(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFEC )))
#define GPIOPCellID0(x)			(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFF0 )))
#define GPIOPCellID1(x)			(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFF4 )))
#define GPIOPCellID2(x)			(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFF8 )))
#define GPIOPCellID3(x)			(*((volatile uint32_*)(MGPIO_OFFSET(x) + 0xFFC )))


#define CLOCK_BASE_ADDRESS  0x400FE000


#define RCGCGPIO_REG				(*((volatile uint32_*)(CLOCK_BASE_ADDRESS + 0x608 )))		


#endif /* MGPIO_PRIVATE_H_ */
