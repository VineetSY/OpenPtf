/*************************************************************************************************
 * Module name: INTRPT.c
 *
 * Purpose: HW/SW interrupt Implementation Module
 *
 * Created on: 18-Apr-2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "Cmn_Types.h"
#include "Project_Cfg.h"
#if ( _INTRPT_MODULE_ == ON )
/*MCU Specific Header File*/
#if (_MCU_STM32L476RG_ == ON)
# include "stm32l4xx.h"
#endif
#if ( _GPIO_MODULE_ == ON )
# include "GPIO.h"
#endif
#if ( _ADC_MODULE_ == ON )
# include "ADC.h"
#endif
#include "LEDApp.h"
#include "PRINT.h"

/*************************************************************************************************
 *	MACRO
 *************************************************************************************************/


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
 *  @name - SysTick_Handler
 *
 *  @summary - SysTick timer default interrupt handler
 *
 *  @param [in] - IRQn	Interrupt Number Definition
 *
 *  @param [in]- priority	programmable priority level of 0-15 for each interrupt
 *
 *  @retval - NA
 *************************************************************************************************/
void INTRPT_Config(uint32 IRQn, uint32 priority)
{
	NVIC_EnableIRQ(IRQn);
	NVIC_SetPriority(IRQn, priority);

	return;
}

/*************************************************************************************************
 *  @name - SysTick_Handler
 *
 *  @summary - SysTick timer default interrupt handler
 *
 *  @param - NA
 *
 *  @retval - NA
 *************************************************************************************************/
void SysTick_Handler(void)
{
//	LEDApp_LED_Update();
	LEDApp_BreatheLED_Update();
	return;
}


/*************************************************************************************************
 *  @name - TIM2_IRQHandler
 *
 *  @summary - TIM2 timer interrupt handler
 *
 *  @param - NA
 *
 *  @retval - NA
 *************************************************************************************************/
void TIM2_IRQHandler(void)
{

	return;
}

/*************************************************************************************************
 *  @name - ADC1_2_IRQHandler
 *
 *  @summary - ADC1 interrupt handler
 *
 *  @param - NA
 *
 *  @retval - NA
 *************************************************************************************************/
extern uint16 adc_in5_value;
extern uint16 adc_in1_value;
void ADC1_2_IRQHandler(void)
{
	static uint16 data1 = 0;
	static uint16 data2 = 0;
	static uint8 sequence = 0;

//	if(ADC1->ISR & ADC_ISR_EOS)
//	{
//		adc_in1_value = data1;
//		adc_in5_value = data2;
//	}
//	else
//	{
//		if(sequence%2)
//		{
//			ADC_GetValue(&data2);
//			sequence = 0;
//
//		}
//		else
//		{
//			ADC_GetValue(&data1);
//			sequence++;
//		}
//	}
//	(void)ADC_Start();

	return ;
}


#endif /*_INTRPT_MODULE_*/
