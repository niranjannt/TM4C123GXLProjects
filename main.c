
#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "SysTick.h"



/**
 * main.c
 */
char volatile hours=1;
char volatile minutes=12;
char volatile seconds=59;
char volatile isPM=0;
char volatile timecounter;
char volatile timecounter2;
void displayScreen(void);
void EnableInterrupts(void);  // Enable interrupts
void Switch_Init(void);
uint32_t Switch_In(void);
uint32_t Switch_In1(void);
uint32_t Switch_In2(void);
uint32_t Switch_In3(void);
uint32_t Switch_In4(void);
uint32_t Switch_In5(void);
void DAC4_Init(void);
uint32_t tickflag;
const uint8_t   ticks2[2113] = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,8,7,8,8,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,8,8,7,8,8,7,8,8,7,8,7,8,7,8,7,8,7,8,7,7,8,7,8,7,8,8,7,8,7,8,7,7,8,7,8,8,7,8,7,7,8,7,8,7,8,7,7,8,7,8,8,7,8,8,7,8,7,7,7,8,8,7,8,7,7,8,7,8,8,7,8,8,7,8,7,8,7,8,8,7,8,8,7,8,8,7,8,8,7,8,7,8,7,8,8,7,8,8,7,8,8,7,8,7,7,8,8,8,8,7,8,8,7,8,8,7,8,8,7,7,7,8,8,8,7,7,8,8,7,8,7,7,8,7,8,8,7,7,8,8,8,7,8,7,7,8,7,8,8,7,8,8,7,7,8,8,7,8,8,7,7,7,8,7,7,7,7,8,7,7,8,8,7,8,8,7,8,8,8,8,8,8,8,7,8,8,8,8,8,8,8,8,7,7,7,7,8,7,8,7,7,8,7,8,7,8,7,7,8,7,8,8,7,8,8,7,7,8,8,7,8,8,7,8,8,8,8,7,7,7,7,7,8,8,7,8,8,7,7,8,8,7,7,7,8,7,8,8,7,8,8,8,7,7,8,8,8,7,7,8,7,7,7,7,8,8,8,8,8,7,7,7,8,8,8,8,7,7,7,7,8,8,7,7,8,8,7,7,7,7,7,8,8,7,7,7,8,8,8,8,8,8,7,7,7,7,7,7,8,8,7,7,7,7,7,8,8,8,8,7,7,7,8,8,8,8,7,7,7,7,7,8,8,7,7,8,8,7,7,7,7,8,8,8,7,7,7,8,8,8,8,7,7,8,8,8,8,8,8,8,7,7,7,7,8,8,8,8,8,7,7,7,7,8,8,8,8,8,8,7,7,7,7,8,7,8,8,8,8,7,7,7,8,7,8,8,7,8,8,7,7,8,8,8,7,8,7,7,7,7,7,7,8,8,7,8,8,7,7,7,8,8,8,8,7,7,7,7,7,8,7,8,8,7,7,7,7,7,8,8,8,7,7,7,7,8,8,8,8,7,7,7,7,8,8,8,7,7,7,7,7,7,8,8,8,8,8,8,8,7,8,8,8,7,7,7,7,8,8,8,7,7,7,7,8,8,7,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,8,8,7,7,7,7,7,8,8,8,8,7,7,7,7,8,7,8,8,8,8,7,7,7,8,8,7,7,8,8,7,8,8,8,7,8,7,8,7,7,7,7,8,7,8,8,7,8,7,7,8,7,7,8,8,8,8,8,7,7,7,7,7,8,8,8,7,7,7,8,7,7,9,8,7,7,7,7,7,7,8,8,8,8,8,6,6,8,7,7,8,8,7,7,7,8,8,8,8,8,7,7,8,8,8,8,8,8,8,7,7,7,7,8,8,8,8,8,7,7,8,8,8,8,8,7,7,7,7,8,7,8,8,7,7,7,7,7,8,8,8,8,7,8,7,7,8,8,8,7,7,8,8,8,7,7,7,7,7,7,7,8,8,8,7,7,8,8,7,7,8,8,8,8,7,8,8,8,7,7,8,7,7,7,7,8,8,8,7,8,8,7,7,7,7,8,8,8,7,8,7,7,7,7,8,8,8,7,8,8,8,8,8,8,7,7,7,7,7,7,8,8,8,7,7,7,7,7,7,7,7,8,8,8,8,8,8,7,7,8,8,8,8,8,8,7,7,7,7,8,7,7,7,7,7,7,8,8,8,8,8,7,7,7,7,7,7,8,8,8,8,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,8,8,7,7,7,7,7,7,8,8,8,8,7,7,7,8,8,8,8,8,8,8,7,7,8,8,8,8,8,8,8,7,7,8,8,8,7,7,7,7,7,7,7,7,8,7,7,7,7,8,8,8,8,8,8,8,7,7,8,8,7,7,7,7,7,7,7,7,8,8,7,7,7,7,7,8,8,8,8,8,8,8,7,7,7,7,8,8,8,8,7,7,7,7,8,8,8,7,7,7,7,7,8,8,8,8,7,7,7,7,7,7,8,8,8,7,7,7,7,7,8,8,8,8,8,8,7,7,7,7,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,8,8,8,7,7,7,7,7,7,8,8,8,8,8,7,7,7,7,7,8,8,8,8,7,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,7,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,8,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,8,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,7,8,8,7,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,8,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,8,8,8,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,8,7,8,7,7,8,8,8,8,8,7,8};
void Timer1A_Init(uint32_t period);
int main(void)
{

    PLL_Init(Bus80MHz);
    ST7735_InitR(INITR_REDTAB);
    Switch_Init();
    DAC4_Init();

    uint32_t last=0, now=0;
    uint32_t last1=0, now1=0;
    uint32_t last2=0, now2=0;
   uint32_t last3=0, now3=0;
    uint32_t last4=0, now4=0;
    uint32_t done=0;

    while(done==0){
        now=Switch_In();
        if((last == 0) && (now==32)){
        last = now;
        }
        else if((last == 32) && (now==0)){
            hours = (hours % 12) + 1;
            last=now;
        }

       //displayScreen();


       now1=Switch_In1();
       if((last1 == 0) && (now1==16)){
       last1 = now1;
       }
       else if((last1 == 16) && (now1==0)){
           minutes=(minutes+1)%60;
           last1=now1;
       }


       now3=Switch_In3();
              if((last3 == 0) && (now3==1)){
              last3 = now3;
              }
              else if((last3 == 1) && (now3==0)){
                  seconds=(seconds+1)%60;
                  last3=now3;
              }



      now2=Switch_In4();
      if((last2 == 0) && (now2==16)){
      last2 = now2;
      }
      else if((last2 == 16) && (now2==0)){
          if(isPM){
              isPM=0;
          }
          else{
              isPM=1;
          }
          last2=now2;
      }




      displayScreen();



      now4=Switch_In2();
      if((last4 == 0) && (now4==16)){
      last4 = now4;
      }
      else if((last4 == 16) && (now4==0)){
      done=1;

    }
    }

    EnableInterrupts();
    SysTick_Init();
    Timer1A_Init(7272);


   while(1){
        displayScreen();
    }


}


void SysTick_Handler(void){
    timecounter++;
    if(timecounter>=5){
        tickflag=1;
       timecounter=0;
       if((hours==11)&&(minutes==59)&&(seconds==59)&&(isPM==1)){
           isPM=0;

       }
       else if((hours==11)&&(minutes==59)&&(seconds==59)&&(isPM==0)){
           isPM=1;

       }
       if(minutes==59 && seconds==59){
              hours = (hours % 12) + 1;
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



if(isPM){
     ST7735_DrawCharS(75, 100, 'P', ST7735_YELLOW, ST7735_BLACK, 2);
     ST7735_DrawCharS(91, 100, 'M', ST7735_YELLOW, ST7735_BLACK, 2);
}
else{
    ST7735_DrawCharS(75, 100, 'A', ST7735_YELLOW, ST7735_BLACK, 2);
    ST7735_DrawCharS(91, 100, 'M', ST7735_YELLOW, ST7735_BLACK, 2);



}


}


void Switch_Init(){

    volatile uint32_t delay;
      SYSCTL_RCGCGPIO_R |= 0x04;  // activate clock for Port C
      delay = SYSCTL_RCGCGPIO_R;  // allow time for clock to start
      GPIO_PORTC_DIR_R &= ~0x20;  // direction PC5 input
      GPIO_PORTC_DEN_R |= 0x20;   // enable PC5 digital port
      volatile uint32_t delay2;
        SYSCTL_RCGCGPIO_R |= 0x04;  // activate clock for Port C
        delay2 = SYSCTL_RCGCGPIO_R;  // allow time for clock to start
        GPIO_PORTC_DIR_R &= ~16;  // direction PC4 input
        GPIO_PORTC_DEN_R |= 16;   // enable PC4 digital port
        volatile uint32_t delay3;
          SYSCTL_RCGCGPIO_R |= 16;  // activate clock for Port E
          delay3 = SYSCTL_RCGCGPIO_R;  // allow time for clock to start
          GPIO_PORTE_DIR_R &= ~16;  // direction PE4 input
          GPIO_PORTE_DEN_R |= 16;   // enable PE4 digital port
          SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
            while((SYSCTL_PRGPIO_R & 0x20) == 0){}; // wait for clock to stabilize
            GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
            GPIO_PORTF_CR_R |= 0x11;          // allow changes to PF0, PF4
            GPIO_PORTF_DIR_R &= ~0x11;        // 3) make PF0, PF4 inputs
            GPIO_PORTF_DEN_R |= 0x11;         // 4) enable digital I/O on PF0, PF4
            GPIO_PORTF_PUR_R |= 0x11;         // 5) enable weak pull-up on PF0, PF4








}

uint32_t Switch_In(void){
    return(GPIO_PORTC_DATA_R&32);


}

uint32_t Switch_In1(void){

    return (GPIO_PORTC_DATA_R&16);



}

uint32_t Switch_In2(void){

    return (GPIO_PORTE_DATA_R&16);



}

uint32_t Switch_In3(void){

    return (GPIO_PORTF_DATA_R&1);


}

uint32_t Switch_In4(void){

    return (GPIO_PORTF_DATA_R&16);


}

uint32_t Switch_In5(void){
    return (GPIO_PORTF_DATA_R&1)|(GPIO_PORTF_DATA_R&16);


}


void DAC4_Init(void){
// Assumes LaunchPad_Init has been called
// I.e., PortB has already been reset and activated (do not reset PortB here again)
  // write this
 //Initialize PB0-PB4 as outputs
    volatile uint32_t delay;
      SYSCTL_RCGCGPIO_R |= 0x08;        // activate clock for Port E
      delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
      GPIO_PORTD_DIR_R |= 0x01;         // set direction to output
      GPIO_PORTD_DEN_R |= 0x01;         // enable digital port
      GPIO_PORTD_DIR_R |= 0x02;         // set direction to output
      GPIO_PORTD_DEN_R |= 0x02;         // enable digital port
      GPIO_PORTD_DIR_R |= 0x04;         // set direction to output
      GPIO_PORTD_DEN_R |= 0x04;         // enable digital port
      GPIO_PORTD_DIR_R |= 0x08;         // set direction to output
      GPIO_PORTD_DEN_R |= 0x08;


// enable digital port

}


void Timer1A_Init(uint32_t period){

  SYSCTL_RCGCTIMER_R |= 0x02;               // 1) activate Timer1
  while((SYSCTL_PRTIMER_R & 0x02) == 0){}   // 2) wait for clock to stabilize
  TIMER1_CTL_R = 0x00000000;                // 3) disable Timer1A during setup
  TIMER1_CFG_R = 0x00000000;                // 4) 32-bit mode
  TIMER1_TAMR_R = 0x00000002;               // 5) periodic mode
  TIMER1_TAILR_R = period - 1;              // 6) set reload value
  TIMER1_TAPR_R = 0;                        // 7) no prescale
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;        // 8) clear timeout flag
  TIMER1_IMR_R = TIMER_IMR_TATOIM;
  NVIC_EN0_R |= (1 << 21);                  // 10) enable IRQ 21 in NVIC (Timer1A)
  TIMER1_CTL_R |= 0x01;                     // 11) enable Timer1A

}

void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;  // acknowledge timeout
  // Do stuff here (e.g., output DAC waveform)
  if(tickflag){
  static uint32_t orange=0;
      GPIO_PORTD_DATA_R = (GPIO_PORTD_DATA_R&(~15)|ticks2[orange]);   // output one value
      orange++;
      if(orange>=2113){
          tickflag=0;
          orange=0;
      }

  }
}






