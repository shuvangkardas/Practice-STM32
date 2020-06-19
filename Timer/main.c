/*
* @file main_timer.c
* @brief Introduction to General purpose timer
* @author Shuvangkar Shuvo 
* @date 30.03.2020
*/

#include "stm32f4xx.h"                 // Device header
int main(void)
{
	/*
	* Enable Clock for different peripherals 
	*/
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN; ///Enable GIPOA Clock 
	GPIOA ->MODER |= GPIO_MODER_MODER5_0;  ///Set PA5 as output
	
	/*
	* Cofigureing General Purpose Timer 2 
	*/
	RCC ->APB1ENR |= RCC_APB1ENR_TIM2EN; ///Enable Timer2 clock
	TIM2 ->PSC = 1600-1;								 ///Clock prescaler. 16MHz/1600 = 10,000
	TIM2 ->ARR = 10000-1;								 ///Frequency = 10,000/prescaler = 1Hz
	TIM2 ->CNT = 0; 										 ///Clear timer counter register to start from zero
	TIM2 ->CR1 |= TIM_CR1_CEN ;					 ///Enable Timer2
	
	while(1)
	{
		/*
		* - Update Interrupt Flag(UIF) will set after 1 second as clock frequency is 1Hz
		* - Update Interrupt Flag(UIF) is set by hardware 
		* - So while loop checks if UIF flag is set
		* - Then in the loop UIF flag have to clear in software for next interrupt
		*/
		while(TIM2 -> SR & TIM_SR_UIF)
		{
			TIM2 -> SR &=~(TIM_SR_UIF);  		///UIF cleared in software
			GPIOA ->ODR ^= GPIO_ODR_ODR_5;	///Toggle PA5
		}
	}

}
