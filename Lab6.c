// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"
#include "TExaS.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
uint32_t previous =1;
uint8_t index=0;
uint32_t key;	


const uint32_t wave[32] = {
  8,9,11,12,13,14,14,15,15,15,14,
  14,13,12,11,9,8,7,5,4,3,2,
  2,1,1,1,2,2,3,4,5,7};

void SysTick_Handler(void) {
	GPIO_PORTB_DATA_R ^=0x10;
	if(key==0){
		DAC_Out(0);
		return;
	}
	DAC_Out(wave[index]);
	index++;
	index%=32;
}

int main(void){
	uint8_t i=0;
	SYSCTL_RCGC2_R = 0xFF;
	i++;
	i++;
	i++;
	i++;
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
  // other initialization
  EnableInterrupts();
	unsigned long Data; // 0 to 15 DAC output
  //PLL_Init();         // like Program 4.6 in the book, 80 MHz
  DAC_Init();
  for(;;) {
    DAC_Out(Data);
    Data = 0x0F&(Data+1); // 0,1,2...,14,15,0,1,2,...
  }
/*  
	while(1){
		key = Piano_In();
		if(previous!= key){
			switch(key){
				case 0x00: Sound_Play(0);
				break;
				case 0x01: Sound_Play(2841); //A 880Hz
				break;
				case 0x02: Sound_Play(2531); //B 987.8Hz
				break;
				case 0x03: Sound_Play(2681); //Bflat Asharp 932.3Hz
				break;
				case 0x04: Sound_Play(2389); //C 1046.5Hz
				break;	
			}		
		}
		previous = key;
			
  }   */ 
}



