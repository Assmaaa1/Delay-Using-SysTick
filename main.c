#include "stm32f4xx.h"                  // Device header


/*

This program allows to generate a delay im milliseconds using the cortex system timer:  SysTick 
and toggling a led accordingly
*/


#define GPIOD_CLCK_EN (1<<3) // enable clock for port D
#define GPIOD_MODE (1<<30) // set pin PD15 as output
#define GPIOD_ODR_Set (1<<15) // set high the led PD15
#define GPIOD_ODR_ReSet (0<<15) // set low the led PD15



void SystickSetup (void);

void SystickDelay(int ms);

int main(void)

{
	RCC->AHB1ENR |= GPIOD_CLCK_EN;
	GPIOD->MODER |= GPIOD_MODE; 
	SystickSetup();

	while (1) 
	
	{		
			 SystickDelay(1000);
			 GPIOD->ODR ^= GPIOD_ODR_Set;
		  
	}

}


void SystickDelay(int ms)
	
{
	  SysTick->LOAD = (8000*ms)-1; 
		while(!(SysTick->CTRL & 0x10000)){} 
	
}

void SystickSetup (void)
	
{	
	 
	 SysTick->VAL = 0; // clear current value
	 SysTick->CTRL = 5; // bit 2 is set to 1 since the clock source is internal , bit 1 is set to 1 to enabling conting down from the reload value 
	 // to zero
	 //and bit 0 is set to 1 to enable counter

}
	
		
		



// number &= ~(1 << x); clear a bit x 
// number |= 1 << x; set the bit x
// number ^= 1 << x; toggle te bit x
