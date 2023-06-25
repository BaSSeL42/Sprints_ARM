/**************************************************************
 *  AUTHOR 		: Bassel Yasser
 *  Version 	: V0.0.0
 *  Date		: 25 - 1 - 2023
 *  Description : LSTD_TYPES.h
 ****************************************************************/

/**********************************************************
 *				 HEADER GUARD OF FILE
 *********************************************************/
#ifndef LSTD_TYPES_H_
#define LSTD_TYPES_H_

/***************************************************
 * 					ERRORS DEFINITION
 **************************************************/
#define FAILED				(0U)
#define SUCCESS				(1U)
#define ERR_INVALID		(2U)

#define ZERO					(0U)

/***************************************************
 * 					POINTER DEFINITION
 **************************************************/
//NULL is void pointer
#ifndef NULL
#define NULL						(void*)(0)
#endif


/***************************************************
 * 					BOOLEAN VALUES
 **************************************************/
#ifndef FALSE
#define FALSE		(0U) // U is saffix --> unsigned integer
#endif

#ifndef TRUE
#define TRUE		(1U) // U is saffix --> unsigned integer
#endif

/***************************************************
 * 					DATA_TYPES
 **************************************************/
typedef unsigned char 					uint8_;
typedef unsigned short int 			uint16_;
typedef unsigned long int 						uint32_;
typedef unsigned long long int  			uint64_;


typedef signed char 						sint8_;
typedef signed short int 				sint16_;
typedef signed long  int 				sint32_;

typedef float		 								float32_;
typedef double 									float64_;

typedef uint8_ 									boolean;





typedef void(*ptr_func_t)(void);




#endif /* LSTD_TYPES_H_ */
