// SysTick.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize the SysTick module, wait at least a
// designated number of clock cycles, and wait approximately a multiple
// of 10 milliseconds using busy wait.  After a power-on-reset, the
// LM4F120 gets its clock from the 16 MHz precision internal oscillator,
// which can vary by +/- 1% at room temperature and +/- 3% across all
// temperature ranges.  If you are using this module, you may need more
// precise timing, so it is assumed that you are using the PLL to set
// the system clock to 80 MHz.  This matters for the function
// SysTick_Wait10ms(), which will wait longer than 10 ms if the clock is
// slower.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the books
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015
   Volume 1, Program 4.7
   
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Program 2.11, Section 2.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void Timer1A_Delay_Init(void) {
  SYSCTL_RCGCTIMER_R |= 0x02;      // activate Timer1
  while((SYSCTL_PRTIMER_R & 0x02) == 0){} // wait for clock to stabilize
  TIMER1_CTL_R = 0x00000000;       // disable Timer1A during setup
  TIMER1_CFG_R = 0x00000000;       // 32-bit timer mode
  TIMER1_TAMR_R = 0x00000001;      // one-shot mode
  TIMER1_CTL_R |= 0x00000000;      // no triggers
}

// Time delay using busy wait.
// This assumes 80 MHz system clock.
void Timer1A_Wait_us(uint32_t time_us) {
  TIMER1_TAILR_R = (time_us * 80) - 1;      // 80 MHz clock, so 1 us = 80 cycles
  TIMER1_ICR_R = 0x00000001;              // clear timeout flag
  TIMER1_CTL_R |= 0x00000001;             // enable Timer1A
  while((TIMER1_RIS_R & 0x01) == 0){}     // wait for timeout
}



void Timer1A_Wait_10ms(uint32_t time_ms) {
  while(time_ms--) {
    Timer1A_Wait_us(10000); // 1000 us = 1 ms
  }
}
