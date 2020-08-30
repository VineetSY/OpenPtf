/*************************************************************************************************
 * Module name: ADC.c
 *
 * Purpose: Analog to Digital converter peripheral device driver.
 *
 * Created on: 28-Jun-2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "Cmn_Types.h"
#include "Project_Cfg.h"

#if ( _ADC_MODULE_ == ON )
/*MCU Specific Header File*/
#if (_MCU_STM32L476RG_ == ON)
# include "stm32l4xx.h"
#endif
#if ( _INTRPT_MODULE_ == ON )
# include "INTRPT.h"
#endif
#include "ADC.h"
/*************************************************************************************************
 *	MACRO & Types
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
 *  @name - ADC_Init
 *
 *  @summary - ADC initialization function. this function will also call the ADC start to start
 *  			the peripheral
 *  			Currently configured for:
 *  			ADC1_IN5 on PA0
 *  			ADC1_IN1 on PC0
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void ADC_Init(void)
{
	/*To start ADC operations, it is first needed to exit deep-power-down mode by setting bit DEEPPWD=0*/
	ADC1->CR &= ~ADC_CR_DEEPPWD;

	/*It is mandatory to enable the ADC internal voltage regulator by setting the bit ADVREGEN=1*/
	ADC1->CR |= ADC_CR_ADVREGEN;
	 /*The software must wait for the startup time of The software must wait for the startup time of the
	 ADC voltage regulator (TADCVREG_STUP) before launching a calibration or enabling the
	 ADC. This delay must be implemented by software.*/
	for (uint32 var = 0; var < 10; ++var)
	{
		//Software delay for ADVREGEN
	}

	/*Channels can be configured to be either single-ended input or differential input by writing
	into bits DIFSEL[15:1] in the ADCx_DIFSEL*/
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_5;
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_1;

	/*Write ADCALDIF=0 before launching a calibration which will be applied for single-
	ended input conversions*/
	ADC1->CR &= ~ADC_CR_ADCALDIF;
	/*ADC Calibration*/
	ADC1->CR &= ~ADC_CR_ADEN;	/*Make sure the ADC is disabled*/
	ADC1->CR |= ADC_CR_ADCAL;	/*calibration is then initiated by software*/
	while(0 != (ADC1->CR & ADC_CR_ADCAL))
	{
		/*wait till calibration is done*/
	}

	/*Select a clock source for the ADC*/
	/*ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;*/ /*This line is disabled as i'm not sure if this is needed.*/

	/*ADC Enable*/
	ADC1->CR |= ADC_CR_ADEN;
	while(0 == (ADC1->ISR & ADC_ISR_ADRDY))
	{
		/*wait till ADC is ready*/
	}

	/*Before any conversion of an input channel coming from GPIO pads, it is necessary to
	configure the corresponding GPIOx_ASCR register in the GPIO, in addition to the I/O
	configuration in analog mode*/
	GPIOA->ASCR |= GPIO_ASCR_ASC0;
	GPIOC->ASCR |= GPIO_ASCR_ASC0;

	/*Select highest sampling time for channel 5.*/
	ADC1->SMPR1 |= ADC_SMPR1_SMP5_1 | ADC_SMPR1_SMP5_0;
	ADC1->SMPR1 |= ADC_SMPR1_SMP1_1 | ADC_SMPR1_SMP1_0;
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;

	/*ADC sequence register set as value 5 and 1 for conversion from ADC1 in ch5 and ch1 as the first and second conversion channels*/
	ADC1->SQR1 |= ADC_SQR1_L_0; /*Sequence length 2*/
	ADC1->SQR1 |= ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_0 | ADC_SQR1_SQ2_0;

	/*continuous conversion mode enable*/
	ADC1->CFGR |= ADC_CFGR_CONT;

	/*Direct memory access enable*/
	ADC1->CFGR |= ADC_CFGR_DMAEN;

	/*Direct memory access configuration  Circular Mode selected*/
	ADC1->CFGR |= ADC_CFGR_DMACFG;

	/*Configure ADC Interrupt with highest Priority*/
	/*INTRPT_Config(ADC1_2_IRQn, 0x00);*/

	/*Enable ADC End of Conversion Interrupt*/
	/*ADC1->IER |= ADC_IER_EOCIE;*/
	ADC1->IER |= ADC_IER_OVRIE;

	(void)ADC_Start();

	return ;
}

/*************************************************************************************************
 *  @name - ADC_Start
 *
 *  @summary -  This function will clear ADC flag and start ADC conversion operation
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void ADC_Start(void)
{

	/* Clear ADC interrupt*/
	//ADC1->ISR |= (ADC_ISR_EOC | ADC_ISR_EOS);
	/*ADC Continuous mode*/
//	ADC1->CFGR |= ADC_CFGR_CONT;
	/*Start conversion*/
	ADC1->CR |= ADC_CR_ADSTART;

	return ;
}

/*************************************************************************************************
 *  @name - ADC_GetValue
 *
 *  @summary - ADC initialization function. this function will also call the ADC start to start
 *  			the peripheral
 *
 *  @param - [in] - *buffer: pointer to buffer to store ADC conversion result from Data register
 *
 *  @retval- NA
 *************************************************************************************************/
void ADC_GetValue(uint16 *buffer)
{
	/*reading the ADCx_DR register clears the EOC interrupt flag in ADCx_ISR*/
	*buffer = (uint16)ADC1->DR;

	return ;
}

/*************************************************************************************************
 *  @name - ADC_Stop
 *
 *  @summary -  This function will Stop ADc operation
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void ADC_Stop(void)
{

	/*Disable ADC interrupt*/
	ADC1->ISR &= ~ADC_ISR_EOC;
	/*Disable ADC operation*/
	ADC1->CR |= ADC_CR_ADDIS;

	return ;
}

#endif /*_ADC_MODULE_*/
