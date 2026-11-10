#include <reg51.h>

/* LED connections */
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;
sbit led4 = P1^4;

/* Keypad rows */
sbit r1 = P2^4;
sbit r2 = P2^5;
sbit r3 = P2^6;
sbit r4 = P2^7;

/* Keypad columns */
sbit c1 = P2^0;
sbit c2 = P2^1;
sbit c3 = P2^2;
sbit c4 = P2^3;


/* Delay function */
void delay(void)
{
    int i;
    int j;

    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 150; j++)
        {
        }
    }
}


/* 7-Segment values for 0-F */
unsigned char code seg[16] =
{
    0x3F,   /* 0 */
    0x06,   /* 1 */
    0x5B,   /* 2 */
    0x4F,   /* 3 */
    0x66,   /* 4 */
    0x6D,   /* 5 */
    0x7D,   /* 6 */
    0x07,   /* 7 */
    0x7F,   /* 8 */
    0x6F,   /* 9 */
    0x77,   /* A */
    0x7C,   /* B */
    0x39,   /* C */
    0x5E,   /* D */
    0x79,   /* E */
    0x71    /* F */
};


void main(void)
{
    int i;   P0 = 0x00;
    while(1)
    {
        c4 = 0;
        c3 = 1;
        c2 = 1;
        c1 = 1;
        r1 = 1;
        r2 = 1;
        r3 = 1;
        r4 = 1;
        led1 = 0;
        led2 = 0;
        led3 = 0;
        led4 = 0;

        if(r4 == 0)
        {
            delay();

            if(r4 == 0)
            {
                P0 = seg[0];
                led1 = 1;
            }
        }
        else if(r3 == 0)
        {
            delay();
            if(r3 == 0)
            {
                P0 = seg[1];
                led2 = 1;
            }
        }
        else if(r2 == 0)
        {
            delay();
            if(r2 == 0)
            {
                P0 = seg[2];
                led3 = 1;
            }
        }
				
        else if(r1 == 0)
        {
            delay();

            if(r1 == 0)
            {
                P0 = seg[3];
                led4 = 1;
            }
        }
        c4 = 1;
        c3 = 0;
        c2 = 1;
        c1 = 1;
        r1 = 1;
        r2 = 1;
        r3 = 1;
        r4 = 1;
        if(r4 == 0)
        {
            delay();
            if(r4 == 0)
            {
                P0 = seg[4];
                led1 = 1;
                led2 = 0;
                led3 = 0;
                led4 = 0;
                delay();

                led1 = 0;
                led2 = 1;
                led3 = 0;
                led4 = 0;
                delay();

                led1 = 0;
                led2 = 0;
                led3 = 1;
                led4 = 0;
                delay();

                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 1;
                delay();

                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 0;
            }
        }

        else if(r3 == 0)
        {
            delay();

            if(r3 == 0)
            {
                P0 = seg[5];

                /* Alternate LEDs */

                led1 = 1;
                led2 = 0;
                led3 = 1;
                led4 = 0;
                delay();

                led1 = 0;
                led2 = 1;
                led3 = 0;
                led4 = 1;
                delay();

                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 0;
            }
        }

        else if(r2 == 0)
        {
            delay();

            if(r2 == 0)
            {
                P0 = seg[6];
                for(i = 0; i < 16; i++)
                {
                    led1 = (i & 1);
                    led2 = (i & 2);
                    led3 = (i & 4);
                    led4 = (i & 8);

                    delay();
                }

                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 0;
            }
        }

        else if(r1 == 0)
        {
            delay();

            if(r1 == 0)
            {
                P0 = seg[7];

                /* All LEDs blink */

                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 1;
                delay();

                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 0;
                delay();
            }
        }

        c4 = 1;
        c3 = 1;
        c2 = 0;
        c1 = 1;

        r1 = 1;
        r2 = 1;
        r3 = 1;
        r4 = 1;

        if(r4 == 0)
        {
            delay();

            if(r4 == 0)
            {
                P0 = seg[8];

                /* LEDs OFF */

                led1 = 0;
                led2 = 0;
                led3 = 0;
                led4 = 0;
            }
        }

        else if(r3 == 0)
        {
            delay();

            if(r3 == 0)
            {
                P0 = seg[9];
            }
        }

        else if(r2 == 0)
        {
            delay();

            if(r2 == 0)
            {
                P0 = seg[10];
            }
        }

        else if(r1 == 0)
        {
            delay();

            if(r1 == 0)
            {
                P0 = seg[11];
            }
        }

        c4 = 1;
        c3 = 1;
        c2 = 1;
        c1 = 0;

        r1 = 1;
        r2 = 1;
        r3 = 1;
        r4 = 1;

        if(r4 == 0)
        {
            delay();

            if(r4 == 0)
            {
                P0 = seg[12];       
            }
        }

        else if(r3 == 0)
        {
            delay();

            if(r3 == 0)
            {
                P0 = seg[13];      
            }
        }

        else if(r2 == 0)
        {
            delay();

            if(r2 == 0)
            {
                P0 = seg[14];      
            }
        }

        else if(r1 == 0)
        {
            delay();

            if(r1 == 0)
            {
                P0 = seg[15];      
            }
        }
    }
}