/*
 * pixel_addressing.c
 *
 *  Created on: Dec 6, 2018
 *      Author: sambagley
 */

#include "pixel_addressing.h" //all our magic functions

/*SendByte function
 * This function does all the magic.
 *  takes one byte, and  bit by bit will send either a ~800 ns high signal
 *  or a ~400 ns high signal to send a 1 or 0, respectively.
 */
void sendByte(unsigned int b){
    unsigned int bit;
    for(bit=0; bit<8; bit++){
        if (b & 0x80){      // Check if MSB is high
                    P4->OUT |= BIT0;    // Send long signal
                    SysCtlDelay(3); //delays 9 clock cycles
                    P4->OUT &= ~BIT0;
                }
                else {
                    P4->OUT |= BIT0;     // Send short signal
                    P4->OUT &= ~BIT0;
                }
        b <<= 1;  // Shift byte left
    }
}

/* this function will takes the individual r , g and b values,
 * equalizes them, scales them back up to 255.
 * Then it sends the data to the LEDs with sendByte*/
void sendPixel(unsigned char r, unsigned char g, unsigned char b){
    sendByte(g*36);
    sendByte(r*36);
    sendByte(b*85);
}

void initWS2812(){
    SysCtlDelay(3000);  // Latch pixel color
    sendPixel(0,0,0);                           // Turn off all pixels
    SysCtlDelay(3000);  // Latch pixel color
}
/* SendFifty Function
 * This function will address all 50 LEDs on the wheel based on the array
 * element that is passed in.
 * It will use it and also the next 49 elements in the array
 * for each proceeding LED.
 *
 *
 * TODO: improve efficiency, change this function, and the script to generate
 *  picture arrays to reuse data for the 25 LEDs that are 180 away from the first 25 instead of
 * just having a unique element for each LED at each location,
 *  as it is now. this will half the size of our arrays.
 */
void sendFifty(char colorMap[], int periodOverTicks)
{
    unsigned int startTime = TIMER32_1->VALUE; // value we will compare against later for timing
   /*start timer with period divided by ticks*/
    unsigned int i = 0;
    for (i = 0; i < 50; i++)
    {
        sendPixel((colorMap[i] & 0b11100000), (colorMap[i] & 0b00011100), (colorMap[i] & 0b00000011));
        if (flaggy == 1 )
           return;
    }
    SysCtlDelay(1700);  // Latch pixel color
   while(TIMER32_1->VALUE > (startTime - periodOverTicks))
   //until we have spent enough time here we will wait so we don't get ahead
   {
       if (flaggy == 1) //if the flag gets set we  will leave anyways
           return;
   }
}

//assembly clock cycles delay function



//
// For CCS implement this function in pure assembly.  This prevents the TI
// compiler from doing funny things with the optimizer.
//
__asm("    .sect \".text:SysCtlDelay\"\n"
      "    .clink\n"
      "    .thumbfunc SysCtlDelay\n"
      "    .thumb\n"
      "    .global SysCtlDelay\n"
      "SysCtlDelay:\n"
      "    subs r0, #1\n"
      "    bne.n SysCtlDelay\n"
      "    bx lr\n");









