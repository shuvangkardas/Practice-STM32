#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void usart_begin(uint32_t baud);
void usart_putChar(int data);
char usart_getChar(void);
void usart_print(char *str);
void delayMs(int delay);

char str[] = "Hi There";
int count = 0; 
int main(void)
{
	usart_begin(9600);	
	while(1)
	{
		//usart_putChar('H');
		//usart_putChar('I');
		usart_print("\nHello world"); 
		//Loop back test
		char data = usart_getChar();
		usart_putChar(data);
		//count++;
		delayMs(1000);
	}
}

void usart_begin(uint32_t baud)
{
	//APB1 bit17: USART clock enable
	//USART2 Connected to PA2
	/*
	RCC -> APB1ENR |= 0x20000; //Enable clock source for usart
	RCC -> AHB1ENR |=1; //Enable clock source for PORTA
	GPIOA -> AFR[0] = 0x0700; //Alternate Function for USART
	GPIOA -> MODER |= 0x0020; //Set PA2 alternate function
	
	USART2 ->BRR =  0x0683;//9600 @16MHz
	USART2 ->CR1 = 0x0008; //Enable TX
	USART2 -> CR1 |= 0x2000;//Enable USART
	
	*/
	RCC ->APB1ENR |= RCC_APB1ENR_USART2EN;  //enable clock for USART
	RCC ->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //Enable clock for PORTA. USART2 is connected with PORTA
	
	GPIOA -> AFR[0] |= 7UL << GPIO_AFRL_AFSEL2_Pos;//Alternte Function for PA2(TX)
	GPIOA -> AFR[0] |= 7UL <<GPIO_AFRL_AFSEL3_Pos; //Alternate function for PA3(RX)
	GPIOA ->MODER |= GPIO_MODER_MODER2_1; //PA2 = TX : Alternate function mode
	GPIOA ->MODER |= GPIO_MODER_MODER3_1; //PA3 = RX : Alternate function mode
	
	
	USART2 ->BRR = 0x0683;//Baud 9600
	USART2 ->CR1  |= USART_CR1_TE; //Transmitter Enable
	USART2 ->CR1   |= USART_CR1_RE; //Receiver Enable
	USART2 ->CR1  |= USART_CR1_UE; //enable USART 
	
	//USART2 ->CR1 |= USART_CR1_RE ; //Receiver Enable
	//USART2 ->CR1 &=~(USART_CR1_M); // 8 data bits and 1 start bit & n stop bit
	//USART2 ->CR2 &= ~(USART_CR2_STOP); //1 stop bit 
	

	
	/*
	*Baud = Fck/(8*(2-OVER8)*USARTDIV)
	* OVER8 = 1;
	* Fck = 16MHz
	* Baud = 9600
	* USARTDIV = 208.375
	* simple way to calculate baud
	* BRR = SystemCoreClock/baud
	*/
	//USART1 -> CR1 |= USART_CR1_OVER8; //Oversampling by 8
	//USART2 ->BRR = SystemCoreClock/baud; //Simple way to calculate baud rate
	/*
	USART2 ->BRR = 0x008B;//Baud 115k
	*/
	
}
void usart_putChar(int data)
{
	//while(!(USART2 -> SR & USART_SR_TXE)); //TXE = 1:Data is transferred to the shift register
	while(!(USART2 -> SR & 0x0080)){}
	USART2 ->DR = (data & 0xFF);
}
void usart_print(char *str)
{
	while(*str != '\0')
	{
		usart_putChar(*str);
		str++;
	}
}

char usart_getChar(void)
{
	while(!(USART2 ->SR & 0x0020)){}
		return USART2 -> DR;
}
void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i = 0; i<3195; i++);
	}
}