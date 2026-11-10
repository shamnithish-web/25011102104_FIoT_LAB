#include <reg52.h>

sbit RS = P3^2;
sbit EN = P3^3;

sbit D4 = P3^4;
sbit D5 = P3^5;
sbit D6 = P3^6;
sbit D7 = P3^7;

void delay_ms(unsigned int ms)
{
    unsigned int i;
    unsigned int j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 120; j++)
        {
        }
    }
}

void lcd_enable()
{
    EN = 1;
    delay_ms(1);
    EN = 0;
    delay_ms(1);
}

void lcd_nibble(unsigned char value)
{
    D4 = value & 0x01;
    D5 = (value >> 1) & 0x01;
    D6 = (value >> 2) & 0x01;
    D7 = (value >> 3) & 0x01;

    lcd_enable();
}

void lcd_cmd(unsigned char value)
{
    RS = 0;

    lcd_nibble(value >> 4);
    lcd_nibble(value & 0x0F);

    delay_ms(2);
}

void lcd_data(unsigned char value)
{
    RS = 1;

    lcd_nibble(value >> 4);
    lcd_nibble(value & 0x0F);

    delay_ms(2);
}

void lcd_init()
{
    RS = 0;
    EN = 0;

    delay_ms(20);

    lcd_nibble(0x03);
    delay_ms(5);

    lcd_nibble(0x03);
    delay_ms(1);

    lcd_nibble(0x03);
    delay_ms(1);

    lcd_nibble(0x02);
    delay_ms(1);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);

    delay_ms(5);
}

void lcd_puts(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}


void main()
{
    lcd_init();
    lcd_puts("HI SIR!!");
	  lcd_puts("Tharak");
    while(1)
    {
    }
}