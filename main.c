#include<lpc21xx.h>
#include"delay.h"
#include"lcd.c"
#include"key.c"
#include"i2c.c"
#include"uart.c"
#include"m.c"

#define gled 1<<17
#define rled 1<<18
#define sw1 1<<14
#define sw2 1<<16

void keyboard(void);
void init(void);
void i2c_pass(void);
void uart_otp(void);

unsigned char pass[7],o[7],otp[7];

int main()
{
	unsigned char i,j;
  init();//initialize all 
	i2c();//i2c password store and read
	i2c_pass();//password return value from i2c to given variable o
	lcd_str("hii");
	while(((IOPIN0>>14)&1)==1);
	while(((IOPIN0>>14)&1)==0)
 {	
	  for(j=0;j<3;j++)
	  {
		  lcd_command(0x01);
      lcd_command(0x80);
	    lcd_str("Enter Pass");
		  key();//keypad value input give
	    keyboard();//input keypad value from key to given variable pass
	  for(i=0;i<6;i++)
	  {
		  if(pass[i] != o[i])//compare input and strore 
		   {
			   break;
		   }
	  }
	    /*lcd_command(0x01);
      lcd_command(0x80);
	    lcd_data(pass[0]);
	    lcd_data(o[0]);*/
	   if(i!= 6)
	   {
		   IOCLR0 |= rled;//password wrong red led
			 delay_ms(500);
			 IOSET0 |= rled;
			 lcd_command(0x01);
       lcd_command(0x80);
	     lcd_str("Re-Enter Pass");
			 delay_sec(1);
			 continue;
	    }
	   else
	   {
		   IOCLR0 |= gled;//password correct green led
			 delay_ms(500);
			 IOSET0 |= gled;//clear led
			 break;
	   }
	  }
	  if(j!=3)
	  {
			lcd_command(0x01);
      lcd_command(0x80);
			lcd_str("press switch");
			my_rand();
		  msg_send();//uart send otp to device as otp
		  uart_otp();//input keypad value from uart to otp
		  for(j=0;j<3;j++)
		 {
			 key();//keypad value input give
	     keyboard();//input keypad value from key to given variable pass
			 for(i=0;i<6;i++)
			 {
				 if(pass[i] != otp[i])//compare input and strore 
		     {
			     break;
		     }
			 }
			  if(i!= 6)
	      {
		      IOCLR0 |= rled;//password wrong red led
			    delay_ms(500);
			    IOSET0 |= rled;//clear led
			    lcd_command(0x01);
          lcd_command(0x80);
	        lcd_str("Re-Enter OTP");
			    continue;
	      }
	      else
	      {
		      IOCLR0 |= gled;//password correct green led
			    delay_ms(500);
			    IOSET0 |= gled;//clear led
				  motor();//motor run
			    break;
	      }
		   }
		  if(j==3)
		  { 
			  lcd_command(0x01);
        lcd_command(0x80);
			  lcd_str("wrong otp");//wrong otp
		  }
	   }

 }
}

void init()
{
	PINSEL0 |=0x00;
	IODIR0 |= gled |rled;
	IOSET0 |=rled|gled;
	key_config();
	lcd_configure();
	i2c_init();
	uart_configure();
	motor_config();
}

void keyboard()
{
	unsigned char i;
	for(i=0;i<6;i++)
  {
    pass[i] =  key_fun(i);
  }
    /*lcd_command(0x01);
    lcd_command(0x80);
   for(i=0;i<6;i++)
   {
     lcd_data(pass[i]);
		 delay_ms(100);
   }*/
}

void i2c_pass()
{
	unsigned char i;
	for(i=0;i<6;i++)
  {
    o[i] =  i2c_fun(i);
  }
	  /*lcd_command(0x01);
    lcd_command(0x80);
   for(i=0;i<6;i++)
   {
     lcd_data(o[i]);
   }*/
}

void uart_otp()
{
	unsigned char i;
	for(i=0;i<6;i++)
  {
    otp[i] =  uart_fun(i);
  }
	  /*lcd_command(0x01);
    lcd_command(0x80);
   for(i=0;i<6;i++)
   {
     lcd_data(otp[i]);
   }*/
}
