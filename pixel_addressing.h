/*
 * pixel_addressing.h
 *
 *  Created on: Dec 6, 2018
 *      Author: sambagley
 */

#ifndef PIXEL_ADDRESSING_H_
#define PIXEL_ADDRESSING_H_
#include "msp.h"
#include <stdbool.h>
#include <stdint.h>
extern int flaggy;// our makeshift flag, will change to a real flag once we figure out how.
void initWS2812();
void sendByte(unsigned int b);
void sendPixel(unsigned char r, unsigned char g, unsigned char b);
void SysCtlDelay(uint32_t ui32Count);
void sendFifty(char colorMap[], int);
#endif /* PIXEL_ADDRESSING_H_ */
