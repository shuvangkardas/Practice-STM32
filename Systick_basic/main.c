/*
* @file SysTick_main.c
* @brief Delay() function using SysTick Timer of STM32
*
* The purpose of the file is to make a delay function using SysTick timer.
*
* @author Shuvangkar Shuvo
* @version v0.1.0
* @date Date 30.03.2020
* @bug no know bugs
*/


#include "stm32f4xx.h"                  // Device header
void sysTickDelay(int n);

int main(void)
{
	RCC ->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; ///Enable clock access to port A
	GPIOA ->MODER |= GPIO_MODER_MODER5_0; ///PA5 to output mode
	/*
	*Configure Systick  to generate 200ms delay 
	*SysTick ->LOAD = 1600000-1; // For 16MHz, 100ms  time
	*SysTick ->VAL = 0;
	*SysTick  ->CTRL |= SysTick_CTRL_ENABLE_Msk; //Enable Systick 
	*/
	while(1)
	{
		GPIOA ->ODR ^= GPIO_ODR_ODR_5;///toggle PA5
		sysTickDelay(100);   
		
	}
	
}

/*
* brief create delay using SysTick Timer.
* The function works in the following way 
* - load the number of cycles to generate per unit delay time
* - Clear the current value of the counter
* - Enable Systick Timer
* - loop until expected delay finishes
* @code 
* for(int i = 0; i<n; i++)
*	{
*		while((SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk)==0);
*	}
* @endcode
*
*@param n  The n is used to input the delay in milisecond
*@return void
*/
void sysTickDelay(int n)
{
	SysTick ->LOAD = 16000; ///For 16MHz, 1ms  time
	SysTick ->VAL = 0;      ///clear current counter register
	SysTick ->CTRL |= SysTick_CTRL_ENABLE_Msk;
	for(int i = 0; i<n; i++)
	{
		//wait until count flag is set
		while((SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk)==0);
	}
}