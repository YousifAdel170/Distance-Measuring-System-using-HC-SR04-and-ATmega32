 /******************************************************************************
 * Module: ICU
 * File Name: icu.c
 * Description: Source file for the AVR ICU driver
 * Author: Yousif Adel
 *******************************************************************************/
#include "icu.h"
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/interrupt.h> /* For ICU ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType *Config_ptr)
{
	/* 1. Configure ICP1/PD6 as i/p pin */
	CLEAR_BIT(DDRD,PD6);

	/* 2. Timer1 always operates in Normal Mode */
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	/*Other way*/
	//	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/* 3. insert the required clock value in the first three bits (CS10, CS11 and CS12)of TCCR1B Register */
	TCCR1B = (TCCR1B & 0xF8) | (Config_ptr->clock);		// 0xF8	[1111 1000]

	/* 4. insert the required edge type in ICES1 bit in TCCR1B Register */
		/* Basic way*/
			//	if( (*Config_ptr->edge) == RAISING)
			//		SETBIT(TCCR1B,ICES1);
			//	if( (*Config_ptr->edge) == FALLING)
			//		CLEARBIT(TCCR1B,ICES1);
		/* Advanced Way */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_ptr->edge)<<6);	// 0xBF	[1011 1111]

	/* 5. Initial Value for Timer1 */
	TCNT1 = 0;

	/* 6. Initial Value for the input capture register */
	ICR1 = 0;

	/* 7. Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMSK,TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}


/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void)
{
	/* 1. Clear All Timer1/ICU Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* 2. Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK,TICIE1);

	/* 3. Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}
