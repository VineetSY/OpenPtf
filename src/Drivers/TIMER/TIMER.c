/*************************************************************************************************
 * Module name: TIMER.c
 *
 * Purpose:
 *
 * Created on: 18-Apr-2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "stm32l4xx.h"
#include "Types.h"
#include "GPIO.h"
#include "INTRPT.h"

/*************************************************************************************************
 *	MACRO
 *************************************************************************************************/
#define INT_PRIORITY_0 (uint32)0


/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/

/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/


/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/

/*************************************************************************************************
 *  @name - TIMER_RLT_Init
 *
 *  @summary - Generic function to initialise/configure the timer as a reload timer
 *
 *  @param - NA
 *
 *  @retval - NA
 *************************************************************************************************/
void TIMER_RLT_Init(void)
{
	/*TIM1 configured as a down counter*/
	TIM2->CR1 |= TIM_CR1_DIR;

	/*TIM1 Pre-scaler Auto reload register value set to max*/
	TIM2 ->ARR |= 0xFFFF;

	/*TIM1 update interrupt enable*/
	TIM2->DIER |= TIM_DIER_UIE;

	/*Enable Interrupt with highest Priority*/
	INTRPT_Config(TIM2_IRQn, INT_PRIORITY_0);

	/*TIM1 Counter enabled*/
	TIM2->CR1 |= TIM_CR1_CEN;

	return;
}

