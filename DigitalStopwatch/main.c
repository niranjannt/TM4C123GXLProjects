
#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "SysTick.h"



/**
 * main.c
 */
char volatile hours=0;
char volatile minutes=0;
char volatile seconds=0;
char volatile timecounter;
void displayScreen(void);
void EnableInterrupts(void);  // Enable interrupts
void Switch_Init(void);
void DisableInterrupts(void);
uint32_t Switch_In5(void);
uint32_t Switch_In4(void);

int main(void)
{

    PLL_Init(Bus80MHz);
    ST7735_InitR(INITR_REDTAB);
    Switch_Init();
    uint32_t last=0, now=0;
    uint32_t last1=0, now1=0;





       //displayScreen();









   while(1){
       now=Switch_In4();
        if((last == 0) && (now==16)){
        last = now;
        }
        else if((last == 16) && (now==0)){
            last=now;
            SysTick_Init();

            EnableInterrupts();

        }

        now1=Switch_In5();
         if((last1 == 0) && (now1==1)){
         last1 = now1;
         }
         else if((last1 == 1) && (now1==0)){
             last1=now1;
             DisableInterrupts();

         }

        displayScreen();
    }


}


void SysTick_Handler(void){
    timecounter++;
    if(timecounter>=5){
       timecounter=0;

       if(minutes==59 && seconds==59){
              hours++;
              minutes=0;
              seconds=0;
              }
       else if(seconds==59){
       minutes=(minutes+1)%60;
       seconds=0;
       }

       else{
   seconds++;
       }
    }





}




 void SysTick_Init(void){

   NVIC_ST_CTRL_R = 0;              // 1) disable SysTick during setup
   NVIC_ST_RELOAD_R = 15999999;   // 2) maximum reload value
   NVIC_ST_CURRENT_R = 0;           // 3) any write to current clears it
   NVIC_ST_CTRL_R = 0x00000007; // Enable SysTick with core clock and interrupt

 }



void displayScreen(){
    ST7735_InvertDisplay(1);
    char timearray[6];
    if(hours>9){
      timearray[0]=hours/10+'0';
      timearray[1]=hours%10+'0';

    }
    else if(hours<=9){
      timearray[0]='0';
      timearray[1]=hours+'0';

    }

    if(minutes>9){
      timearray[2]=minutes/10+'0';
      timearray[3]=minutes%10+'0';
    }

    else if(minutes<=9){
      timearray[2]='0';
      timearray[3]=minutes+'0';

    }
    if(seconds>9){
      timearray[4]=seconds/10+'0';
      timearray[5]=seconds%10+'0';
    }
    else if(seconds<=9){
     timearray[4]='0';
     timearray[5]=seconds+'0';

    }






     ST7735_DrawCharS(19, 40, timearray[0], ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(37, 40, timearray[1], ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(55, 40, ':', ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(73, 40, timearray[2], ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(91, 40, timearray[3], ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(57, 70, ':', ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(75, 70, timearray[4], ST7735_YELLOW, ST7735_BLACK, 3);
     ST7735_DrawCharS(93, 70, timearray[5], ST7735_YELLOW, ST7735_BLACK, 3);





}


void Switch_Init(){
    SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
            while((SYSCTL_PRGPIO_R & 0x20) == 0){}; // wait for clock to stabilize
            GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
            GPIO_PORTF_CR_R |= 0x11;          // allow changes to PF0, PF4
            GPIO_PORTF_DIR_R &= ~0x11;        // 3) make PF0, PF4 inputs
            GPIO_PORTF_DEN_R |= 0x11;         // 4) enable digital I/O on PF0, PF4
            GPIO_PORTF_PUR_R |= 0x11;         // 5) enable weak pull-up on PF0, PF4








}


uint32_t Switch_In5(void){
    return (GPIO_PORTF_DATA_R&1);


}


uint32_t Switch_In4(void){

    return (GPIO_PORTF_DATA_R&16);
}




