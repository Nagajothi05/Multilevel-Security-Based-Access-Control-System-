#include<LPC21XX.h>

void delay_sec(unsigned char );

void delay_ms(unsigned int d)
{
	T0PR = 15000-1;
	T0TCR = 0x01;
	while(T0TC<d);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void delay_sec(unsigned char d)
{
	T0PR = 15000000-1;
	T0TCR = 0x01;
	while(T0TC<d);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
