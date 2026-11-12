#include <reg51.h>
void uart_init() {
    TMOD = 0x20; // Timer 1 Mode 2 (8-bit auto-reload)
    TH1 = 0xFD;  // 9600 Baud @ 11.0592 MHz
    SCON = 0x50; // Mode 1, 8-bit UART, enable receiver
    TR1 = 1;     // Start Timer 1
}
void uart_tx(char c) {
    SBUF = c;
    while(!TI);
    TI = 0;
}
char uart_rx() {
    while(!RI);
    RI = 0;
    return SBUF;
}
void main() {
    char ch;
    uart_init();
    while(1) {
        ch = uart_rx();
        uart_tx(ch); // Echo received character back
    }
}
