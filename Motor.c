#include<lpc21xx.h>

#define m1 1<<21
#define m2 1<<22

void motor_config(void);
	
void motor()
{
	IOSET0 |= m1;
	IOCLR0 |= m2;
	delay_sec(5);
	IOCLR0 |= m1|m2;
		
	IOCLR0 |= m1;
	IOSET0 |= m2;
	delay_sec(5);
	IOCLR0 |= m1|m2;
}

void motor_config()
{
	PINSEL1 |=0x00;
	IODIR0 |= m1|m2;
}
	
