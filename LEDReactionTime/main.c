

#include <stdio.h>
#include <stdint.h>
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include <stdlib.h>
#include "SysTick.h"
#include "ST7735.h"
#include <string.h>
/**
 * main.c
 */
uint32_t delay_counter;

void LED_Init(void);
void Switch_Init(void);
uint32_t Switch_In(void);
void SysTick_Init(uint32_t period);
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);
void LED_Out(uint32_t data);// restore I bit to previous value
uint32_t switchpressed=0;
uint32_t ledon=0;
char reactiontime[30];

void uintToStr(uint32_t num, char* buf);
int main(void){
  PLL_Init(Bus80MHz);
  LED_Init();
  Switch_Init();
  uint32_t last=0, now=0;
  SysTick_Init(80000);
  ST7735_InitR(INITR_REDTAB);
  Timer1A_Delay_Init();
  EnableInterrupts();
int randnum=0;
  while(1){
      char passed[50]="Reaction Time: ";
      now=Switch_In();//PC4 for Switch corresponds to red led
      if((last == 0) && (now==16)){
          Timer1A_Wait_10ms(1);
          if((last==0)&&(now==16)){
          last = now;
          switchpressed=1;
          }
          last=now;
      }

      else if((last == 16) && (now==0)){
          last=now;
      }

randnum=rand()%11;
if(randnum==5){
    LED_Out(1);
    ledon=1;
}
if(switchpressed==1 && ledon==1){
    ledon=0;
    switchpressed=0;
    uintToStr(delay_counter,reactiontime);
    char ms[]=" ms";
    strcat(reactiontime, ms);
    ST7735_SetCursor(1,2);
    ST7735_OutString(passed);
    ST7735_SetCursor(1,4);
    ST7735_OutString(reactiontime);
    Timer1A_Wait_10ms(300);
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_SetCursor(0,0);
    LED_Out(0);
    Timer1A_Wait_10ms(300);
    delay_counter=0;

}



  }
}

void SysTick_Handler(void){
if(ledon==1 && switchpressed==0){
    delay_counter++;
}

}

void uintToStr(uint32_t num, char* buf) {
    int i = 0;
    char temp[30];
    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    while (num > 0) {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }
    int j=0;
    for (j = 0; j < i; j++) {
        buf[j] = temp[i - j - 1];
    }
    buf[i] = '\0';
}



void LED_Out(uint32_t data){
    if(data)
        GPIO_PORTB_DATA_R |= 64;
    else
        GPIO_PORTB_DATA_R &= ~64;
}




void SysTick_Init(uint32_t period){long sr;
  sr = StartCritical();
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
                              // enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = 0x07;
  EndCritical(sr);
}





void LED_Init(void){
    volatile uint32_t delay;
      SYSCTL_RCGCGPIO_R |= 2;      // activate clock for Port E
      delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
      GPIO_PORTB_DIR_R |= 64;         // set direction to output
      GPIO_PORTB_DEN_R |= 64;         // enable digital port
      GPIO_PORTB_DIR_R |= 128;       // set direction to output
      GPIO_PORTB_DEN_R |= 128;       // enable digital port
      GPIO_PORTB_DIR_R |= 4;       // set direction to output
      GPIO_PORTB_DEN_R |= 4;       // enable digital port

}

void Switch_Init(void){

    volatile uint32_t delay;
      SYSCTL_RCGCGPIO_R |= 0x04;  // activate clock for Port C
      delay = SYSCTL_RCGCGPIO_R;  // allow time for clock to start
      GPIO_PORTC_DIR_R &= ~16;  // direction PC4 input
      GPIO_PORTC_DEN_R |= 16;   // enable PC4 digital port








}

uint32_t Switch_In(void){
    return(GPIO_PORTC_DATA_R&16);


}



