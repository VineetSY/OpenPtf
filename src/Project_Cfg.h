/*************************************************************************************************
 * Module name: Project_Cfg.h
 *
 * Purpose: All project specific configurations to  be done here. MCU variant selection, Features
 * 			selection, etc.
 *
 * Created on: 01-May-2020
 *
 * Author: Vineet
 *************************************************************************************************/

#ifndef PROJECT_CFG_H_
#define PROJECT_CFG_H_


/*************************************************************************************************
 *	Includes
 *************************************************************************************************/

/*************************************************************************************************
 *	MACRO
 *************************************************************************************************/
/*MCU configuration*/
#ifndef _MCU_STM32L476RG_
# define _MCU_STM32L476RG_				ON
# define _CORTEX_M4_CMSIS_				ON
#endif


/*MODULE Configuration*/
#ifndef _PRINT_MODULE_
#define _PRINT_MODULE_					ON
#endif
#ifndef _GPIO_MODULE_
#define _GPIO_MODULE_					ON
#endif
#ifndef _TIMER_MODULE_
#define _TIMER_MODULE_					ON
#endif
#ifndef _INTRPT_MODULE_
#define _INTRPT_MODULE_					ON
#endif
#ifndef _CLOCK_MODULE_
#define _CLOCK_MODULE_					ON
#endif

/*************************************************************************************************
 *	Private variables
 *************************************************************************************************/


/*************************************************************************************************
 *	Global variables
 *************************************************************************************************/


#endif /* PROJECT_CFG_H_ */
