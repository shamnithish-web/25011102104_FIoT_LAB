#include <reg51.h>
// 16x2 LCD in 4-bit Mode with 4x4 Matrix Keypad on Port 0
sbit RS = P2^0;
sbit EN = P2^1;
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0;i<ms;i++) for(j=0;j<120;j++);
}
void lcd_cmd(unsigned char cmd) {
    P2 = (P2 & 0x0F) | (cmd & 0xF0);
    RS = 0; EN = 1; delay_ms(1); EN = 0;
    P2 = (P2 & 0x0F) | ((cmd << 4) & 0xF0);
    RS = 0; EN = 1; delay_ms(1); EN = 0;
}
void lcd_data(unsigned char dat) {
    P2 = (P2 & 0x0F) | (dat & 0xF0);
    RS = 1; EN = 1; delay_ms(1); EN = 0;
    P2 = (P2 & 0x0F) | ((dat << 4) & 0xF0);
    RS = 1; EN = 1; delay_ms(1); EN = 0;
}
void lcd_init() {
    delay_ms(20);
    lcd_cmd(0x28); // 4-bit mode, 2 lines, 5x8 font
    lcd_cmd(0x0C); // Display ON, Cursor OFF
    lcd_cmd(0x06); // Increment cursor
    lcd_cmd(0x01); // Clear display
    delay_ms(2);
}
void main() {
    lcd_init();
    lcd_data('K');
    lcd_data('E');
    lcd_data('Y');
    lcd_data(':');
    while(1);
}
