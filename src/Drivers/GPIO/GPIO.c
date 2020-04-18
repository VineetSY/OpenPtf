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
	__IO uint32_t AHB2ENR; /* RCC->AHB2ENR Reset and clock control - Advanced high performance bus */
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
IOPinCfgTable_t IOPinCfg[TOTAL_GPIO_PIN] =
{
	/* AHB2ENR,            MODER0,              MODER1,              OTYPER,           OSPEEDR0,                OSPEEDR1,                PUPDR,             BSRR,           BRR*/
	{RCC_AHB2ENR_GPIOAEN,  GPIO_MODER_MODE5_0,  GPIO_MODER_MODE5_1,  GPIO_OTYPER_OT5,  GPIO_OSPEEDR_OSPEED5_0,  GPIO_OSPEEDR_OSPEED5_1,  GPIO_PUPDR_PUPD5,  GPIO_BSRR_BS5,  GPIO_BRR_BR5},
	{RCC_AHB2ENR_GPIOAEN,  GPIO_MODER_MODE6_0,  GPIO_MODER_MODE6_1,  GPIO_OTYPER_OT6,  GPIO_OSPEEDR_OSPEED6_0,  GPIO_OSPEEDR_OSPEED6_1,  GPIO_PUPDR_PUPD6,  GPIO_BSRR_BS6,  GPIO_BRR_BR6}
};

/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/

/*************************************************************************************************
 *	Private function prototypes
 *************************************************************************************************/
void GPIO_Pin_Config(GPIO_PinType_e Pin);

/*************************************************************************************************
 *	Function Definitions
 *************************************************************************************************/



/**************************************************************************************************
 *  @name - GPIO_Port_Init
 *
 *  @summary - Generic function to initialize the GPIO pins
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void GPIO_Port_Init(void)
{

	/*Reset and clock control - Advanced high performance bus- Enabling GPIO Port A*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIO_Pin_Config(GPIO_PA5);
	GPIO_Pin_Config(GPIO_PA6);

/*
	//Setup control registers for the LED output
	//Mode Register for output
	GPIOA ->MODER |= (GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0);
	GPIOA ->MODER &= ~(GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1);

	//Output type register (push pull)
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT5 | GPIO_OTYPER_OT6);

	//SPEED Register (High speed)
	GPIOA ->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0 | GPIO_OSPEEDR_OSPEED5_1 | GPIO_OSPEEDR_OSPEED6_0 | GPIO_OSPEEDR_OSPEED6_1;

	//Pull up pull down register
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6);

	//Bit set reset register
	//Turn ON the LED at PA5 and PA6
	GPIOA ->BSRR |= (GPIO_BSRR_BS5 | GPIO_BSRR_BS6); //set pin 5,6 on port A
*/

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
	//Setup control registers
	//Mode Register for output
	GPIOA ->MODER |= (IOPinCfg[Pin].MODER0);
	GPIOA ->MODER &= ~(IOPinCfg[Pin].MODER1);

	//Output type register (push pull)
	GPIOA ->OTYPER &= ~(IOPinCfg[Pin].OTYPER);

	//SPEED Register (High speed)
	GPIOA ->OSPEEDR |= (IOPinCfg[Pin].OSPEEDR0 | IOPinCfg[Pin].OSPEEDR1);

	//Pull up pull down register
	GPIOA ->PUPDR &= ~(IOPinCfg[Pin].PUPDR);

	//Bit set reset register
	GPIOA ->BSRR |= (IOPinCfg[Pin].BSRR);

	return;
}

/**************************************************************************************************
 *  @name - GPIO_PinMode_Update
 *
 *  @summary - GPIO pin digital output mode update
 *
 *  @param in - Pin: GPIO pin number to select
 *
 *  @param in - Mode: output mode for the selected pin
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



