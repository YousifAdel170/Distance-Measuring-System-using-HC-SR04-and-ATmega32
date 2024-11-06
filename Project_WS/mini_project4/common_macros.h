 /******************************************************************************
 * Module: Common - Macros
 * File Name: Common_Macros.h
 * Description: Commonly used Macros
 * Author:	Yousif Adel
 *******************************************************************************/
#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)		(REG |= (1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT)		(REG &= ~(1<<BIT))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)		(REG ^= (1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR_BIT(REG,num)		(REG = (REG>>num) | (REG<<(8-num)) )
    /*note that sizeof used for general microcontrollers*/
	//#define ROR_BIT(REG,num)	(REG = (REG>>num) | (REG<<(8*(sizeof(REG))-BIT)))

/* Rotate left the register value with specific number of rotates */
#define ROL_BIT(REG,num)		(REG = (REG<<num) | (REG>>(8-num)) )

/*Get the value of bit in specific register*/
#define GET_BIT(REG,BIT)		( (REG &(1<<BIT)) >> BIT)

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT)		(REG & (1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */
#define	BIT_IS_CLEAR(REG,BIT)	(!(REG & (1<<BIT)))




#endif	/*COMMON_MACROS_H_*/
