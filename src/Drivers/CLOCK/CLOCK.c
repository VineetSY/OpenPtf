/*************************************************************************************************
 * Module name: CLOCK.c
 *
 * Purpose: Handling of all Clock configuration including Peripheral clock enable.
 *
 * Created on: Apr 21, 2020
 *
 * Author: Vineet
 *************************************************************************************************/


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/
#include "stm32l4xx.h"
#include "Types.h"

/*************************************************************************************************
 *	MACRO & Types
 *************************************************************************************************/
#define PLL_80MHZ ( (RCC_PLLCFGR_PLLREN |RCC_PLLCFGR_PLLM_2 | RCC_PLLCFGR_PLLM_0 | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_2 | RCC_PLLCFGR_PLLSRC_MSI) )

#define CLOCK_HSI		0x01u
#define CLOCK_MSI		0x02u
#define CLOCK_PLL_ON	0x01u
#define CLOCK_PLL_OFF	0x00u

/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/

/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/
static void CLOCK_SysClk_Config(uint32 ClkSrc, uint32 PllState);

/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/


/*************************************************************************************************
 *  @name - CLOCK_Init
 *
 *  @summary - System clock Initialization, peripheral clock enable
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void CLOCK_Init(void)
{

	CLOCK_SysClk_Config((uint32)CLOCK_MSI, (uint32)CLOCK_PLL_ON);

	/*Enabling GPIO Port A Clock*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	/*Timer TIM2 clock enable*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	return;
}

/*************************************************************************************************
 *  @name - CLOCK_Init
 *
 *  @summary - System clock Initialization, peripheral clock enable
 *
 *  @param in - ClkSrc: Clock Source for SysClk
 *  				@arg @ref CLOCK_HSI  HighSpeedInternal 16Mhz clock enable
 *  				@arg @ref CLOCK_MSI  MultiSpeedInternal clock enable
 *
 *  @param in - PllState: PLL state for the SysClk
 *  				@arg @ref CLOCK_PLL_ON  PLL Output for Sysclk enable
 *  				@arg @ref CLOCK_PLL_OFF  PLL Output for Sysclk disable
 *  				Currently PLL only supported with CLOCK_MSI
 *
 *  @retval- NA
 *************************************************************************************************/
void CLOCK_SysClk_Config(uint32 ClkSrc, uint32 PllState)
{

	/****************************************************************************
	 * 			Enable High Speed Internal Clock (HSI = 16 MHz)
	 *****************************************************************************/
	if(CLOCK_HSI == ClkSrc)
	{
		RCC->CR |= ((uint32_t)RCC_CR_HSION);

		/* wait until HSI is ready*/
		while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}

		/* Select HSI as system clock source*/
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

		/* Wait till HSI is used as system clock source*/
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
	}

	/****************************************************************************
	 * 			Multi Speed Internal Clock (MSI = 48MHz)
	 *****************************************************************************/
	if(CLOCK_MSI == ClkSrc)
	{
		if((RCC->CFGR & RCC_CFGR_SWS_MSI) !=  RCC_CFGR_SWS_MSI)
		{
			/*MSI can be configured when OFF*/
			RCC->CR &= ~(RCC_CR_MSION);
		}

		/*Flash wait latency for 48mhz HCLK is 2WS*/
		FLASH->ACR &= ~(FLASH_ACR_LATENCY_0WS);
		FLASH->ACR |= (FLASH_ACR_LATENCY_2WS);

		/*Clear MSIRANGE in CR register and then Configure it for Range 11 ie 48MHz*/
		RCC->CR &= ~(RCC_CR_MSIRANGE);
		RCC->CR |= RCC_CR_MSIRANGE_11;

		/*Select MSI range from CR register*/
		RCC->CR |= RCC_CR_MSIRGSEL;
		/*Turn ON MSI and then wait for it to get Ready*/
		RCC->CR |= (RCC_CR_MSION);
		while((RCC->CR & RCC_CR_MSIRDY) == 0) {;}

		/*Switch Main clock to MSI*/
		RCC->CFGR &= ~(RCC_CFGR_SW);
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_MSI;
	}

	/****************************************************************************
	 * 			Enable PLL Clock (PLL_CLK = 80 MHz)
	 *****************************************************************************/
	if( (CLOCK_PLL_ON == PllState) && (CLOCK_MSI == ClkSrc) )
	{
		/*PLL can be configured when OFF*/
		RCC->CR &= ~(RCC_CR_PLLON);

		RCC->PLLCFGR |= (PLL_80MHZ);

		/*Turn ON PLL and then wait for it to get Ready*/
		RCC->CR |= (RCC_CR_PLLON);
		while((RCC->CR & RCC_CR_PLLON) == 0) {;}

		/*Switch Main clock to PLL*/
		RCC->CFGR &= ~(RCC_CFGR_SW);
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
	}

	return;
}

