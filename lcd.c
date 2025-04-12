#include<LPC21XX.H>
//#include"delay.h"

#define lcd 0xff<<4
#define rs 1<<12
#define e 1<<13

void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_configure(void);
void lcd_str(unsigned char *);

void lcd_configure(void)
{
	IODIR0 |=lcd | rs |e;
	lcd_command(0x01);
	lcd_command(0x02);
	lcd_command(0x0c);
	lcd_command(0x38);
	lcd_command(0x80);
}
void lcd_command(unsigned char cmd)
{
	IOCLR0 |= lcd;
	IOSET0 |= cmd<<4;
	IOCLR0 |= rs;
	IOSET0 |= e;
	delay_ms(2);
	IOCLR0 |= e;
}
void lcd_data(unsigned char d)
{
	IOCLR0 |= lcd;
	IOSET0 |= d<<4;
	IOSET0 |= rs;
	IOSET0 |= e;
	delay_ms(2);
	IOCLR0 |= e;
}

void lcd_str(unsigned char *p)
{
	while(*p)
		lcd_data(*p++);
}
