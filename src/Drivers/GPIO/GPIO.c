/*************************************************************************************************
 * Module name: GPIO.c
 *
 * Purpose: Configuration of all GPIO pins and PORT modes.
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
#if ( _GPIO_MODULE_ == ON )
/*MCU Specific Header File*/
#if (_MCU_STM32L476RG_ == ON)
# include "stm32l4xx.h"
#endif


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

static GPIO_BtnState_e GPIO_BtnB1_State = BtnNotPressed;

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
 *  @name - GPIO_BtnB1State_Get
 *
 *  @summary - Button B1 state read
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
GPIO_BtnState_e GPIO_BtnB1State_Get(void)
{
	return GPIO_BtnB1_State;
}

/**************************************************************************************************
 *  @name - GPIO_BtnB1_Config
 *
 *  @summary - Nucleo Board User Button B1 at PC13
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void GPIO_BtnB1_Config(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	/*PC13 input pin config*/
	GPIOC ->MODER &= ~(GPIO_MODER_MODE13);
	GPIOC ->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR13);
	GPIOC ->PUPDR &= ~(GPIO_OSPEEDER_OSPEEDR13);

	return;
}

/**************************************************************************************************
 *  @name - GPIO_UsrBtnB1_Update
 *
 *  @summary - Button B1 state
 *
 *  @param - NA
 *
 *  @retval- NA
 *************************************************************************************************/
void GPIO_UsrBtnB1_Update(void)
{
	/*TODO: ADD debounce logic*/
	if ( !(GPIOC->IDR & GPIO_IDR_ID13) )
	{
		GPIO_BtnB1_State = BtnPressed;
	}
	else
	{
		GPIO_BtnB1_State = BtnNotPressed;
	}

	return ;
}


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
	GPIO_BtnB1_Config();

	return;
}


/**************************************************************************************************
 *  @name - GPIO_Pin_Config
 *
 *  @summary - GPIO pin configuration update
 *
 *  @param [in] - Pin: GPIO pin number to configure
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
 *  @param [in] - Pin: GPIO pin number to select
 *  				@arg @ref GPIO_PA5  GPIO port a pin 5
 *  				@arg @ref GPIO_PA6  GPIO port a pin 5
 *
 *  @param [in] - Mode: output mode for the selected pin
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

#endif /*_GPIO_MODULE_*/
