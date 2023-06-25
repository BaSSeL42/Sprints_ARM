#ifndef SYS_CONTROL_PRIVATE_H
#define	SYS_CONTROL_PRIVATE_H



#define SYS_CONTROL_RCC																	*((volatile uint32_ *) 0x400FE060)
#define SYSDIV																					23
#define USESYSDIV																				22
#define PWRDN																						13
#define BYPASS																					11
#define XTAL																						6
#define OSCSRC																					4
#define MOSCDIS																					0


#define SYS_CONTROL_RCC2																*((volatile uint32_ *) 0x400FE070)
#define USERCC2																					31
#endif