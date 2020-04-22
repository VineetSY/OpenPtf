/*************************************************************************************************
 * Module name: GPIO.c
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

/*************************************************************************************************
 *	MACRO & Types
 *************************************************************************************************/
typedef	struct IOPinCfgTable_st
{
	__IO uint32_t MODER0;  /* GPIO port mode register 0 value*/
	__IO uint32_t MODER1;  /* GPIO port mode register 1 value*/
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR0;
	__IO uint32_t OSPEEDR1;
	__IO uint32_t PUPDR;
	__IO uint32_t BSRR;
	__IO uint32_t BRR;
} IOPinCfgTable_t;


/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/
static IOPinCfgTable_t IOPinCfg[TOTAL_GPIO_PIN] =
{
	/* MODER0,              MODER1,              OTYPER,           OSPEEDR0,                OSPEEDR1,                PUPDR,             BSRR,           BRR*/
	{GPIO_MODER_MODE5_0,  GPIO_MODER_MODE5_1,  GPIO_OTYPER_OT5,  GPIO_OSPEEDR_OSPEED5_0,  GPIO_OSPEEDR_OSPEED5_1,  GPIO_PUPDR_PUPD5,  GPIO_BSRR_BS5,  GPIO_BRR_BR5},
	{GPIO_MODER_MODE6_0,  GPIO_MODER_MODE6_1,  GPIO_OTYPER_OT6,  GPIO_OSPEEDR_OSPEED6_0,  GPIO_OSPEEDR_OSPEED6_1,  GPIO_PUPDR_PUPD6,  GPIO_BSRR_BS6,  GPIO_BRR_BR6}
};

/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/

/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/
static void GPIO_Pin_Config(GPIO_PinType_e Pin);

/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/



/**************************************************************************************************
 *  @name - GPIO_Init
 *
 *  @summary - Generic function to initialize the GPIO pins
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void GPIO_Init(void)
{

	GPIO_Pin_Config(GPIO_PA5);
	GPIO_Pin_Config(GPIO_PA6);

	return;
}


/**************************************************************************************************
 *  @name - GPIO_Pin_Config
 *
 *  @summary - GPIO pin configuration update
 *
 *  @param in - Pin: GPIO pin number to configure
 *
 *  @retval- NA
 **************************************************************************************************/
void GPIO_Pin_Config(GPIO_PinType_e Pin)
{
	/*Setup control registers*/
	/*Mode Register for output*/
	GPIOA ->MODER |= (IOPinCfg[Pin].MODER0);
	GPIOA ->MODER &= ~(IOPinCfg[Pin].MODER1);

	/*Output type register (push pull)*/
	GPIOA ->OTYPER &= ~(IOPinCfg[Pin].OTYPER);

	/*SPEED Register (High speed)*/
	GPIOA ->OSPEEDR |= (IOPinCfg[Pin].OSPEEDR0 | IOPinCfg[Pin].OSPEEDR1);

	/*Pull up pull down register*/
	GPIOA ->PUPDR &= ~(IOPinCfg[Pin].PUPDR);

	/*Bit set reset register*/
	GPIOA ->BRR |= (IOPinCfg[Pin].BRR);

	return;
}

/**************************************************************************************************
 *  @name - GPIO_PinMode_Update
 *
 *  @summary - GPIO pin digital output mode update
 *
 *  @param in - Pin: GPIO pin number to select
 *  				@arg @ref GPIO_PA5  GPIO port a pin 5
 *  				@arg @ref GPIO_PA6  GPIO port a pin 5
 *
 *  @param in - Mode: output mode for the selected pin
 *  				@arg @ref MODE_LOW  GPIO pin digital output low mode
 *  				@arg @ref MODE_HIGH  GPIO pin digital output high mode
 *
 *  @retval- NA
 **************************************************************************************************/
void GPIO_PinMode_Update(uint8 Pin, uint8 Mode)
{
	switch(Mode)
	{
		case MODE_LOW:
			GPIOA ->BRR |= (IOPinCfg[Pin].BRR);
			break;

		case MODE_HIGH:
			GPIOA ->BSRR |= (IOPinCfg[Pin].BSRR);
			break;

		default:
			break;
	}

	return;
}

