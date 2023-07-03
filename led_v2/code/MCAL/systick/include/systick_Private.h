#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_


#define SYSTICK_BASE_ADDRESS				 0xE000E000

#define STCTRL_REG						(*((volatile uint32_*)(SYSTICK_BASE_ADDRESS + 0x010 )))
#define STRELOAD_REG					(*((volatile uint32_*)(SYSTICK_BASE_ADDRESS + 0x014 )))
#define STCURRENT_REG					(*((volatile uint32_*)(SYSTICK_BASE_ADDRESS + 0x018 )))



#define ENABLE_IDX		(0U)

#define INTEN_IDX			(1U)

#define CLK_SRC_IDX		(2U)

#define COUNT_IDX			(16U)

#endif /*SYSTICK_PRIVATE_H_*/

