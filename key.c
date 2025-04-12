#include<lpc21xx.h>
//#include"delay.h"
//#include"lcd.c"

#define col1 (IOPIN1&(1<<20))
#define col2 (IOPIN1&(1<<21))
#define col3 (IOPIN1&(1<<22))
#define col4 (IOPIN1&(1<<23))
#define row1 (1<<16)
#define row2 (1<<17)
#define row3 (1<<18)
#define row4 (1<<19)

unsigned char keypad(void);
void keyp(void);
unsigned char key_fun(unsigned char );
void key(void);
unsigned char p1[7];

void key()
{
	unsigned char i;
	lcd_command(0x01);
  lcd_command(0x80);
	lcd_str("4x4 keypad");
	lcd_command(0xc0);
	
	for(i=0;i<6;i++)
	{
		p1[i]=keypad();
		delay_ms(150);
		while((col1 && col2 && col3 && col4)==0);
	}
	keyp();
}
void key_config()
{
	PINSEL1 |= 0x00000000;
	IODIR1 |= row1|row2|row3|row4;
}

unsigned char keypad(void)
{
	unsigned char key;
	IOCLR1 |= row1|row2|row3|row4;//|1<<20|1<<21|1<<22|1<<23;
	while(1)
	{
		while((col1 && col2 && col3 && col4)==1);
		IOCLR1 |= row1;
		IOSET1 |= row2|row3|row4;
		
		if(col1==0)
		{
			key='7';
			delay_ms(50);
			return key;
		}
		else if(col2==0)
		{
			key='8';
			delay_ms(50);
			return key;
		}
		else if(col3==0)
		{
			key='9';
			delay_ms(50);
			return key;
		}
		else if(col4==0)
		{
			key='/';
			delay_ms(50);
			return key;
		}
		
		IOCLR1 |= row2;
		IOSET1 |= row1|row3|row4;
		
		if(col1==0)
		{
			key='4';
			delay_ms(50);
			return key;
		}
		else if(col2==0)
		{
			key='5';
			delay_ms(50);
			return key;
		}
		else if(col3==0)
		{
			key='6';
			delay_ms(50);
			return key;
		}
		else if(col4==0)
		{
			key='*';
			delay_ms(50);
			return key;
		}
		
		IOCLR1 |= row3;
		IOSET1 |= row2|row1|row4;
		
		if(col1==0)
		{
			key='1';
			delay_ms(50);
			return key;
		}
		else if(col2==0)
		{
			key='2';
			delay_ms(50);
			return key;
		}
		else if(col3==0)
		{
			key='3';
			delay_ms(50);
			return key;
		}
		else if(col4==0)
		{
			key='-';
			delay_ms(50);
			return key;
		}
		
		IOCLR1 |= row4;
		IOSET1 |= row2|row3|row1;
		
		if(col1==0)
		{
			key='o';
			delay_ms(50);
			return key;
		}
		else if(col2==0)
		{
			key='0';
			delay_ms(50);
			return key;
		}
		else if(col3==0)
		{
			key='=';
			delay_ms(50);
			return key;
		}
		else if(col4==0)
		{
			key='+';
			delay_ms(50);
			return key;
		}
	}
}
void keyp()
{
	unsigned char i;
	for(i=0;i<6;i++)
	{
	  lcd_data(p1[i]);
	}
	delay_ms(500);
}
unsigned char key_fun(unsigned char i)
{
	return p1[i];
}
