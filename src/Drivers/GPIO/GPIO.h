/*
 * GPIO.h
 *
 *  Created on: 17-Apr-2020
 *      Author: Vineet
 */

#ifndef GPIO_H_
#define GPIO_H_


/* Global macro */

#define MODE_HIGH (uint8)1
#define MODE_LOW (uint8)0

/* Global function prototypes */
void IOPortInit(void);
void IOPinMode(uint8 Pin, uint8 Mode);

#endif /* GPIO_H_ */
