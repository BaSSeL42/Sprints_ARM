/**************************************************************
 *  AUTHOR 		: Bassel Yasser
 *  Version 	: V0.0.0
 *  Date		: 25 - 1 - 2023
 *  Description : LBIT_MATH.h
 **************************************************************/

/**********************************************************
 *				 HEADER GUARD OF FILE
 *********************************************************/
#ifndef LBIT_MATH_H_
#define LBIT_MATH_H_

/**********************************************************
 *				Function Like Macro
 *********************************************************/
#define SET_BIT(REG , BITNUM)			(REG)   |=  (1U << (BITNUM))
#define CLR_BIT(REG , BITNUM)			(REG)   &= ~(1U << (BITNUM))
#define TOG_BIT(REG , BITNUM)			(REG)   ^=  (1U << (BITNUM))
#define GET_BIT(REG , BITNUM)			(((REG) >> (BITNUM)) & 1U )
//#define GET_BIT_STATUS(REG , BITNUM)			(((REG) >> (BITNUM)) & 1U )

#define SET_BITS(REG , MSK)		(REG) |= (MSK)
#define CLR_BITS(REG , MSK)		(REG) &= (MSK)
#define TOG_BITS(REG , MSK)		(REG) ^= (MSK)

#define SET_ALL_BITS(REG)		(REG) |=  (0xFF)
#define CLR_ALL_BITS(REG)		(REG) &= ~(0x000000FF)
#define TOG_ALL_BITS(REG)		(REG) ^=  (0xFF)


#define HWREG32(_X)      (*((volatile uint32_ *)(_X)))

#endif /* LBIT_MATH_H_ */
