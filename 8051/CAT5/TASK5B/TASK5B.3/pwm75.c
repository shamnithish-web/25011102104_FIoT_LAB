#include <reg51.h>
sbit PWM_LED = P1^1;
void delay_us(unsigned int us) { while(us--); }
void main() {
    // 75% Duty Cycle PWM: 750us ON, 250us OFF (Period = 1ms)
    while(1) {
        PWM_LED = 1;
        delay_us(75);
        PWM_LED = 0;
        delay_us(25);
    }
}
