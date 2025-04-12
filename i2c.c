#include<LPC21XX.H>

typedef unsigned char u8;

void i2c_eep_page_write(u8 ,u8 ,u8 * ,u8 );
void i2c_eep_page_read(u8 ,u8 ,u8 * ,u8 );
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
u8 i2c_nack(void);
u8 i2c_masterack(void);
void i2c_write(u8 );
void i2c_init(void);
void i2c(void);
unsigned char i2c_fun(unsigned char );


u8 p[7];
void i2c()
{
	i2c_eep_page_write(0x50,0x00,"556677",6);
	i2c_eep_page_read(0x50,0x00,p,6);
}

void i2c_init()
{
	PINSEL0 |= 0x00000050;
	I2SCLL = 75;
	I2SCLH = 75;
	I2CONSET = 1<<6;
}

void i2c_eep_page_write(u8 slave_addr,u8 buff_addr,u8 *m,u8 byte)
{
	u8 i;
  i2c_start();	
	i2c_write(slave_addr<<1);
	i2c_write(buff_addr);
	for(i=0;i<byte;i++)
	   i2c_write(m[i]);
	i2c_stop();
	delay_ms(10);
}

void i2c_eep_page_read(u8 slave_addr,u8 buff_addr,u8 *p,u8 byte)
{
	u8 i;
  i2c_start();	
	i2c_write(slave_addr<<1);
	//i2c_write((slave_addr << 1) | 0);
	i2c_write(buff_addr);
	i2c_restart();
	i2c_write(slave_addr<<1 | 1);
	for(i=0;i<byte-1;i++)
	   p[i] = i2c_masterack();
	p[i] = i2c_nack();
	i2c_stop();
	delay_ms(10);
}

void i2c_start()
{
	I2CONSET = 1<<5;
	
	while(((I2CONSET)&(1<<3)) == 0);
	I2CONCLR = 1<<5;
}

void i2c_restart()
{
	I2CONSET = 1<<5;
	I2CONCLR = 1<<3;
	while(((I2CONSET)&(1<<3)) == 0);
	I2CONCLR = 1<<5;
}

void i2c_stop()
{
	I2CONSET = 1<<4;
	I2CONCLR = 1<<3;
}

u8 i2c_nack()
{
	I2CONSET = 0x00;
	I2CONCLR = 1<<3;
	while(((I2CONSET)&(1<<3)) == 0);
	return I2DAT;
}

u8 i2c_masterack()
{
	I2CONSET = 0x04;
	I2CONCLR = 1<<3;
	while(((I2CONSET)&(1<<3)) == 0);
	I2CONCLR = 0x04;
	return I2DAT;
}

void i2c_write(u8 data)
{
	I2DAT = data;
	I2CONCLR = 1<<3;
	while(((I2CONSET)&(1<<3)) == 0);
}
unsigned char i2c_fun(unsigned char i)
{
	return p[i];
}
