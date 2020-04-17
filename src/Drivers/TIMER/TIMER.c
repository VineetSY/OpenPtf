/*
 * INIT.c
 *
 *  Created on: 05-Apr-2020
 *      Author: Vineet
 */


/* Includes */
#include "stm32l4xx.h"
#include "Types.h"
#include "GPIO.h"


/* Private macro */

#define INT_PRIORITY_0 (uint32)0

/* Interrupt Priorities are WORD accessible only under ARMv6M                   */
/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _SHP_IDX(IRQn)           ( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >>    2UL)      )
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

/* Private variables */
typedef	struct IOPinCfgTable_st
{
	__IO uint32_t AHB2ENR; /*!< RCC->AHB2ENR Reset and clock control - Advanced high performance bus >!*/
	__IO uint32_t MODER;   /*GPIOA ->MODER GPIO port mode register,*/

} IOPinCfgTable_t;

/* Private function prototypes */

/* Private functions */


/**************************************************************************************************
 *  @name - ReloadTimerInit
 *
 *  @summary - Generic function to initialise/configure the timer as a reload timer
 *
 *  @param - NA
 *
 *  @retval - NA
 **************************************************************************************************/
void ReloadTimerInit(void)
{
	/*Timer TIM1 clock enable*/
//	RCC->APB2ENR |= RCC_APB2ENR_TIM2EN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	/*TIM1 configured as a down counter*/
	TIM2->CR1 |= TIM_CR1_DIR;

	/*TIM1 Pre-scaler Auto reload register value set to max*/
	TIM2 ->ARR |= 0xFFFF;

	/*TIM1 update interrupt enable*/
	TIM2->DIER |= TIM_DIER_UIE;

	/*Enable Interrupt in NVIC*/
	NVIC->ISER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)TIM2_IRQn) & 0x1FUL));

	/*Set Interrupt Priority*/
	NVIC->IP[_IP_IDX(TIM2_IRQn)]  = ((uint32_t)(NVIC->IP[_IP_IDX(TIM2_IRQn)]  & ~(0xFFUL << _BIT_SHIFT(TIM2_IRQn))) |
	       (((INT_PRIORITY_0 << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << _BIT_SHIFT(TIM2_IRQn)));

	/*TIM1 Counter enabled*/
	TIM2->CR1 |= TIM_CR1_CEN;

	return;
}

/**************************************************************************************************
 *  @name - TIM2_IRQHandler
 *
 *  @summary - TIM2 timer interrupt handler
 *
 *  @param - NA
 *
 *  @retval - NA
 **************************************************************************************************/
void TIM2_IRQHandler(void)
{
	static uint32 i;
	i++;
	//Turn OFF the LED at port PA5
	if(i > 100000)
	{
		i = 0;
		//			LameTask1();
		IOPinMode((uint8)1, (uint8)MODE_LOW);
	}
	else if (i == 50000)
	{
		//			LameTask2();
		IOPinMode((uint8)1, (uint8)MODE_HIGH);
	}
	else
	{
		//Do nothing
	}

	return;
}

