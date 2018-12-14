

#include "pixel_addressing.h"
#include "images.h" //contains all of the data for our images


#define TIMER_PERIOD 0xffffffff

unsigned int period = 10000000;

int flaggy=0; // this variable will help us exit our addressing function early
                //if we finished too slow due to the wheel speeding up.
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
      P2->DIR |= BIT7;
      P4->DIR |= BIT0;
      initWS2812();               // Set up LEDS, turn them off
      P3->DIR &= ~BIT0;           //set up 3.0 as input for hall effect sensor
      P1->REN = BIT0;             // Enable resistor network
      P3->OUT = BIT0;             //turn on pull-up
      /* set the interrupt edge select on pin P4.0 to a low to high transition */
      P3->IES |= BIT0;
      /* clear the interrupt for pin P4.0 */
      P3->IFG = 0x00;
      /* enable the interrupt for pin P4.0 */
      P3->IE = BIT0;
      _enable_interrupts();
      NVIC->ISER[1] = 0x00000020;

      TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_PRESCALE_1 | TIMER32_CONTROL_SIZE;
      TIMER32_1->CONTROL &= ~TIMER32_CONTROL_MODE;

      /* set the initial count of Timer32 module 0 to the TIMER_PERIOD constant */
      TIMER32_1->LOAD = TIMER_PERIOD;

      _enable_interrupts();

      initWS2812();
      SysCtlDelay(100);
   int i = 0;
   int j = 0;
   int k = 0;
   while(1)//repeat forever, or at least until we add in power managment
   {

       //a bunch of for loops to display each array a certain amount of times
       // in retrospect we should just make a function that does this so our main isn't so ugly
     /* for(j = 0; j< 50; j++)
    {
         for(i = 0; i < 180; i++)
         {
            sendFifty(hello[i], period/180);
         }
         flaggy = 0;
      }
      for(j = 0; j< 50; j++)
      {
         for(i = 0; i < 180; i++)
         {
            sendFifty(project[i], period/180);
         }
         flaggy = 0;
      }
      for(j = 0; j< 50; j++)
      {
         for(i = 0; i < 180; i++)
         {
            sendFifty(flag[i], period/180);
         }
         flaggy = 0;
      }*/
      for(j = 0; j< 50; j++)
      {
         for(i = 0; i < 180; i++)
         {
            sendFifty(mario[i], period/180);
         }
         flaggy = 0;
      }
      for(j = 0; j< 50; j++)
      {
         for(i = 0; i < 180; i++)
         {
            sendFifty(crimbus[i], period/180);
         }
         flaggy = 0;
      }
      for(k=0;k<5; k++){
          for(j = 0; j< 3; j++)
          {
             for(i = 0; i < 180; i++)
             {
                sendFifty(pika1[i], period/180);
             }
             flaggy = 0;
          }
          for(j = 0; j< 3; j++)
          {
             for(i = 0; i < 180; i++)
             {
                sendFifty(pika2[i], period/180);
             }
             flaggy = 0;
          }
          for(j = 0; j< 3; j++)
          {
             for(i = 0; i < 180; i++)
             {
                sendFifty(pika3[i], period/180);
             }
             flaggy = 0;
          }
          for(j = 0; j< 3; j++)
          {
             for(i = 0; i < 180; i++)
             {
                sendFifty(pika4[i], period/180);
             }
             flaggy = 0;
          }
      }


   }
}
/*
void T32_INT2_IRQHandler(void){
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;            // Enable sleep on exit from this ISR
    TIMER32_2->INTCLR = 0x00;                       // Clear interrupt
     //TIMER32_2->CONRTOL &= ~CONTROL_ENABLE;         // Turn off timer 32_2
}
*/
void PORT3_IRQHandler(void){
   //SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;              // Disable sleep on exit from this ISR
   P3->IFG = 0x00;                                    //clear interrupt flag
   flaggy = 1;
   TIMER32_1->CONTROL &= ~TIMER32_CONTROL_ENABLE;     // re-set the initial count of Timer32 module 0 to the TIMER_PERIOD constant
   period = TIMER_PERIOD - TIMER32_1->VALUE;
   /*if (period >= 0x0000ffff){                         //  If timer period is getting short, start timer32_2 to enter LPM
       TIMER32_2->LOAD = 0x0f;
       TIMER32_2->CONTROL |= TIMER32_CONTROL_ENABLE;
   }
   */
   TIMER32_1->LOAD = TIMER_PERIOD;
   /* start the Timer32 module 0 */
   TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;
}
