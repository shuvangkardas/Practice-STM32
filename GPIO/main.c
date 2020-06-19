#include "stm32f4xx.h"                  // Device header

void delayMs(int delay);

int main(void)
{
	//Enable clock for PORTA
	RCC ->AHB1ENR |= 1<< 0; //Enable Clock for PORTA
	RCC ->AHB1ENR |= 1<<2; //Enable clock for PORTC
	//Set PA5 as output mode
	GPIOA -> MODER  |= 1<<10; //Set PA5 as output mode
	GPIOC -> MODER  &= ~((1<<27)|(1<<26)); //Set PC13 as input mode

	
	while(1)
	{
		int buttonState = (GPIOC -> IDR ) & ( 1<<13); //check if button is pressed or not
		if(buttonState)
		{
			GPIOA -> ODR &= ~(1<<5); //clear PA5 pin
		}
		else
		{
			GPIOA -> ODR |= 1<<5; //Set PA5 pin
		}
		
		//delayMs(1000);
		
		//delayMs(1000);
		
	}
}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i = 0; i<3195; i++);
	}
}