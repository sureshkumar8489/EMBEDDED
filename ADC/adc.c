#include "stm32f4xx.h"

void delayMs(int n)
{
	for(;n<0;n--)
		for (int i=0;i<3195;i++);
}
int result;
int main(void)
{
	/* set pin 5 for led*/
	RCC->AHB1ENR |=1; 	/*enable GPIOA clock*/
	GPIOA->MODER &= ~0x00000C00;	/*Clear pin*/
	GPIOA->MODER |=0x00000400;	/*Set pin for output*/

	/*Setup pin1 for analog input*/
	RCC->AHB1ENR |=1;	/*Analog GPIOA clock*/
	GPIOA->MODER |=0xC; /*PA1 analog*/

	/*Setup ADC1*/

	RCC->APB2ENR |= 0x00000100; 	/*Enable ADC clock*/
	ADC1->CR2 =0; 	/*SW trigger*/
	ADC1->SQR3 =1;	/*conversion started at ch1*/
	ADC1->SQR1=0;	/*conversion sequence length 1*/
	ADC1->CR2 |=1;	/*enable ADC1*/

	while(1)
	{
		delayMs(100);
		ADC1->CR2 |= 0x40000000;	/*start conversation*/
		while(! (ADC1->SR &2))	/*wait for complete the conversation*/
		 result=ADC1->DR;	/*read result*/
		if(result &0x100)
			GPIOA->BSRR = 0x0000020;	/*LED ON*/
		else
			GPIOA->BSRR = 0x00200000;	/*LED OFF*/
	}
}
