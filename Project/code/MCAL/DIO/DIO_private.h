#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

#include "../../COM/bit_math.h"
#include "../../COM/std_types.h"

#define RCGCGPIO																(*((volatile uint32_t*)0x400FE608))


#define DIO_PORTA_APB														0x40004000
#define DIO_PORTA_AHB 													0x40058000
#define DIO_PORTB_APB 													0x40005000
#define DIO_PORTB_AHB 													0x40059000
#define DIO_PORTC_APB 													0x40006000
#define DIO_PORTC_AHB 													0x4005A000
#define DIO_PORTD_APB 													0x40007000
#define DIO_PORTD_AHB 													0x4005B000
#define DIO_PORTE_APB 													0x40024000
#define DIO_PORTE_AHB 													0x4005C000
#define DIO_PORTF_APB 													0x40025000
#define DIO_PORTF_AHB 													0x4005D000





#define GPIOLOCK																0x520
#define GPIOCR																	0x524

#define GPIODATA																0x000
#define GPIODIR																	0x400
#define GPIODR2R																0x500
#define GPIODR4R																0x504
#define GPIODR8R																0x508
#define GPIOODR																	0x50C
#define GPIOPUR																	0x510
#define GPIOPDR																	0x514
#define GPIODEN																	0x51C
#define GPIOCR																	0x524
#define GPIOPCTL																0x52C

#define VALUE_TO_UNLOCK													0x4C4F434B
#endif