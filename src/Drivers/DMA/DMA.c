/*************************************************************************************************
 * Module name: DMA.c
 *
 * Purpose: Direct Memory Access Peripheral Device Driver
 *
 * Created on: Aug 23, 2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "Cmn_Types.h"
#include "Project_Cfg.h"

#if ( _DMA_MODULE_ == ON )
/*MCU Specific Header File*/
#if (_MCU_STM32L476RG_ == ON)
# include "stm32l4xx.h"
#endif
#if ( _INTRPT_MODULE_ == ON )
# include "INTRPT.h"
#endif
#include "DMA.h"

/*************************************************************************************************
 *	MACRO & Types
 *************************************************************************************************/


/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/
extern uint16 ADC1_Data_Buffer[2];
/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/


/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/

/*************************************************************************************************
 *  @name - DMA_Init
 *
 *  @summary - Initialise and configure the DMA to read ADC1 data
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void DMA_Init(void)
{
	/*DMA channel 1 peripheral address register configured to read from ADC1 DR*/
	DMA1_Channel1->CPAR |= (uint32)(&(ADC1->DR));

	/*DMA channel 1 memory address register configured to write data to ADC_DMA_Buffer*/
	DMA1_Channel1->CMAR |= (uint32)(&ADC1_Data_Buffer);

	/*DMA channel 1 number of data register configured to 2 */
	DMA1_Channel1->CNDTR |= 0x00000002;

	/*DMA channel 1 configuration register Circular mode enabled*/
	DMA1_Channel1->CCR |= DMA_CCR_CIRC;

	/*DMA channel 1 configuration register Memory increment mode enabled*/
	DMA1_Channel1->CCR |= DMA_CCR_MINC;

	/*DMA channel 1 configuration register Peripheral size configured to 16bits*/
	DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0;

	/*DMA channel 1 configuration register Memory size configured to 16bits*/
	DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0;

	DMA_Start();

	return ;
}

/*************************************************************************************************
 *  @name - DMA_Start
 *
 *  @summary - Start DMA operation
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void DMA_Start(void)
{
	/*DMA channel 1 configuration register Channel enabled*/
	SET_BIT(DMA1_Channel1->CCR, DMA_CCR_EN);

	return ;
}

/*************************************************************************************************
 *  @name - DMA_Stop
 *
 *  @summary - Stop DMA operation
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void DMA_Stop(void)
{
	/*DMA1 channel configuration register Channel disabled*/
	CLEAR_BIT(DMA1_Channel1->CCR, DMA_CCR_EN);

	return ;
}

/*************************************************************************************************
 *  @name - DMA_Shutdown
 *
 *  @summary - Shutdown DMA peripheral completely
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void DMA_Shutdown(void)
{

	return ;
}

#endif /*_DMA_MODULE_*/
