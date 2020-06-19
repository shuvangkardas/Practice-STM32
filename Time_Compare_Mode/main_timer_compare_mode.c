/*
* @file main_timer_compare_mode.c
*
* In this example , Timer directcly controls GPIO pin in compare mode
* 
* @author Shuvangkar Shuvo 
*	@date 30.03.2020
*/

#include "stm32f4xx.h"                  // Device header
int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;      ///Enable GIPOA Clock 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;       ///Enable Timer2 clock
	
	GPIOA->MODER |= GPIO_MODER_MODER5_1;      ///Set PA5 as alternate function mode
	GPIOA->AFR[0]|= GPIO_AFRL_AFRL5_0;        ///AF1- alternate function for TIM1/Tim2
	
	TIM2->PSC     = 1600-1;								    ///Clock prescaler. 16MHz/1600 = 10,000
	TIM2->ARR     = 10000-1;								  ///Frequency = 10,000/prescaler = 1Hz
	TIM2->CCMR1  |= 3UL << TIM_CCMR1_OC1M_Pos;///Toggle on compare match
	TIM2->CCR1    = 0;                        ///Set match mode 
	TIM2->CNT     = 0; 								        ///Clear timer counter register to start from zero
	TIM2->CCER   |= TIM_CCER_CC1E;            ///Enable ch1 compare mode
	TIM2->CR1    |= TIM_CR1_CEN ;					    ///Enable Timer2
	
	while(1)
	{
		
	}
}
