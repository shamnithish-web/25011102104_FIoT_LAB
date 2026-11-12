#include <reg51.h>
// Stepper motor sequence on P1.4 - P1.7 via ULN2003
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0;i<ms;i++) for(j=0;j<120;j++);
}
void main() {
    unsigned char step[] = {0x10, 0x20, 0x40, 0x80};
    unsigned char i;
    while(1) {
        for(i = 0; i < 4; i++) {
            P1 = step[i];
            delay_ms(50);
        }
    }
}
