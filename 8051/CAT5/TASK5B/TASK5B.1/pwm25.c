#include <reg51.h>
sbit PWM_LED = P1^1;
void delay_us(unsigned int us) { while(us--); }
void main() {
    // 25% Duty Cycle PWM: 250us ON, 750us OFF (Period = 1ms)
    while(1) {
        PWM_LED = 1;
        delay_us(25);
        PWM_LED = 0;
        delay_us(75);
    }
}
