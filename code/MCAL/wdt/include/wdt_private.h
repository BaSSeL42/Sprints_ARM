
#ifndef MCAL_WDT_PRIVATE_H_
#define MCAL_WDT_PRIVATE_H_



#define WDTLOAD(x)			(*((volatile uint32_*)(0x40000000 + ((x) == 0? 0:1000) )))
#define WDTVALUE(x)			(*((volatile uint32_*)(0x40000004 + ((x) == 0? 0:1000) )))
#define WDTCTL(x)				(*((volatile uint32_*)(0x40000008 + ((x) == 0? 0:1000) )))
#define WDTICR(x)				(*((volatile uint32_*)(0x4000000C + ((x) == 0? 0:1000) )))
#define WDTRIS(x)				(*((volatile uint32_*)(0x40000010 + ((x) == 0? 0:1000) )))
#define WDTMIS(x)				(*((volatile uint32_*)(0x40000014 + ((x) == 0? 0:1000) )))
#define WDTTEST(x)			(*((volatile uint32_*)(0x40000418 + ((x) == 0? 0:1000) )))
#define WDTLOCK(x)			(*((volatile uint32_*)(0x40000C00 + ((x) == 0? 0:1000) )))


#ifndef CLOCK_BASE_ADDRESS
#define CLOCK_BASE_ADDRESS  0x400FE000
#endif

#define RCGCWD_REG				(*((volatile uint32_*)(CLOCK_BASE_ADDRESS + 0x600 )))		




#ifndef WRC_IDX
#define WRC_IDX			(31U)
#endif


#ifndef INTEN_IDX
#define INTEN_IDX			(0U)
#endif

#ifndef RESEN_IDX
#define RESEN_IDX			(1U)
#endif


#ifndef INTTYPE_IDX
#define INTTYPE_IDX			(2U)
#endif

#ifndef STALL_IDX
#define STALL_IDX			(8U)
#endif


#ifndef WDTRIS_IDX
#define WDTRIS_IDX			(0U)
#endif



#endif /*MCAL_WDT_PRIVATE_H_*/


