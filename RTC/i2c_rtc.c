#include<stdio.h>
#include"stm32f4xx.h"
#define SALVE_ADDR 0xD0

void delayMs(int n);
void i2c1_init(void);
void i2c1_burstwrite(char sadder,char madder,int n,char*data);

int main(void)
{
	//char timedatetoset[20]=
		//	i2c1_init;
			//i2c1_burstwrite(SLAVE_ADDR,0,7,timedatetoset);

	while(1)
	{}
	{
		void i2c1_init(void)
	}
	RCC->AHB1ENR |= 0x3;		/*GPIO A & B enable*/
	GPIOB->MODER &=~0xf000; 	/*clear PB7 PB6 bits*/
	GPIOB->MODER |0xA000;		/*PB7 & PB8 bits set for alternate function*/

	/*configure PB6 & PB7 for i2c1*/
	GPIOB->AFR[0] & =~ 0xff000000;	/*clear PB6 & PB7 bits*/
	GPIOB->AFR[0] |=0x44000000;		//PB7 PB6 bits i2c1_SDA i2c1_SCL

	GPIOB->OTYPER |=0xC0;			//output type of the I/O port : Output open-drain
	GPIOB->PUPDR &= ~0xF000;		//clrear PB7 PB6 bits
	GPIOB->PUPDR |= 0x5000;			//Pull-up

	I2C1->CR1 = 0x8000;				//SWRST: Software reset
	I2C1->CR1 &= ~0x8000;			//out of reset
	I2C1->CR2 |= 0x0010;				//12c working @16MHz
	I2C1->CCR |= 0x80;				//standard mode,100khz clock
	I2C1->TRISE = 17;               //maximum raise time
	I2C1->CR1 = 0x0001;				//enable 12c
}
