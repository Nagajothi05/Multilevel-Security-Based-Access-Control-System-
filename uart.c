#include<LPC21XX.H>

void uart_configure(void);
void uart_trans(unsigned char);
void uart_str(unsigned char *);
void uart_receive(void);
void msg_send(void);
void my_rand(void);

unsigned char p2[7];

void uart_configure()
{
	PINSEL0 |= 0x00000005;
	U0LCR = 0x83;
	U0DLM = 0;
	U0DLL = 97;
	U0LCR = 0x03;
}

void uart_trans(unsigned char d)
{
	while((U0LSR & 1<<5) == 0);
	U0THR = d;
}

void uart_str(unsigned char *p)
{
	while(*p)
		uart_trans(*p++);
}

void uart_receive(void)
{
	while((U0LSR & 1<<0) == 0);
		uart_trans(U0RBR);
}

void msg_send()
{
	uart_str("AT\r\n");
	//uart_receive();
	delay_ms(100);
	uart_str("ATE0\r\n");
	//uart_receive();
	delay_ms(100);
	uart_str("AT+CMGF=1\r\n");
	delay_ms(1000);
	uart_str("AT+CMGS=\"9790225314\"\r\n");
	delay_ms(100);
	uart_str("OTP is\r");
	uart_str(p2);
	uart_trans(0x1A);
}
unsigned char uart_fun(unsigned char i)
{
	return p2[i];
}
void my_rand()
{
	unsigned char i;
	unsigned int n=111111;;
	while(((IOPIN0>>16)&1)==1);
	while(((IOPIN0>>16)&1)==0)
	{
		n++;
		if(n>999999)
		{
			n=111111;
		}
	}
	for(i=0;i<6;i++)
	{
		p2[i]=(n%10)+48;
		n=n/10;
	}
	p2[i]='\0';
}

