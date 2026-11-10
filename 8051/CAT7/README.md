# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-7 |
| **DATE** | 24/08/2026 (Week 7) |
| **NAME OF EXP** | 16x2 LCD Driver Development and Dynamic Display Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 + 16x2 Alphanumeric LCD (HD44780) + 4x4 Keypad + Keil C51 |
| **TASK NO** | Task 7A: LCD 4-Bit Init & Display, Task 7B: Cursor Positioning, Task 7C: Keypad Cursor Movement |

---

## 1. Problem Statement

Develop a modular Embedded C driver for an HD44780-compatible 16x2 alphanumeric liquid crystal display in 4-bit nibble mode. Implement:
1. **Task 7A**: LCD initialization sequence and string printing routines (`lcd_init()`, `lcd_cmd()`, `lcd_data()`, `lcd_puts()`).
2. **Task 7B**: Absolute DDRAM cursor positioning (`lcd_goto(row, col)`) and numeric formatting.
3. **Task 7C**: Interactive 4x4 keypad navigation to move a displayed character dynamically across the 16x2 grid (Key 2: Up, Key 8: Down, Key 4: Left, Key 6: Right).

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Pin Mapping (4-Bit Mode)
- `P3.2` -> **RS** (Register Select: 0 = Command, 1 = Data)
- `P3.3` -> **EN** (Enable Strobe: High-to-Low transition latches nibble)
- `P3.4` -> **D4** (Data Bit 4)
- `P3.5` -> **D5** (Data Bit 5)
- `P3.6` -> **D6** (Data Bit 6)
- `P3.7` -> **D7** (Data Bit 7)
- `R/W` (Pin 5) -> Tied to Ground (Write-only mode)
- `V0` (Pin 3) -> 10 kΩ potentiometer center wiper for contrast control
- `VDD/VSS` -> +5V and GND power rails

---

## 3. Core Logic & Initialization Sequence

### 4-Bit Initialization Protocol
Because the HD44780 powers on in 8-bit mode, a specific software reset sequence is required:
1. Wait $>15\ \text{ms}$ after power-on.
2. Send nibble `0x03` three times with appropriate delays.
3. Send nibble `0x02` to switch the controller to 4-bit interface mode.
4. Issue Command `0x28`: 4-bit mode, 2 display lines, 5x8 font.
5. Issue Command `0x0C`: Display ON, cursor OFF, blink OFF.
6. Issue Command `0x06`: Entry mode set (auto-increment cursor).
7. Issue Command `0x01`: Clear display screen.

### Source Code (`LCD.c`)
```c
#include <reg52.h>

sbit RS = P3^2;
sbit EN = P3^3;
sbit D4 = P3^4;
sbit D5 = P3^5;
sbit D6 = P3^6;
sbit D7 = P3^7;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void lcd_enable() {
    EN = 1;
    delay_ms(1);
    EN = 0;
    delay_ms(1);
}

void lcd_nibble(unsigned char value) {
    D4 = value & 0x01;
    D5 = (value >> 1) & 0x01;
    D6 = (value >> 2) & 0x01;
    D7 = (value >> 3) & 0x01;
    lcd_enable();
}

void lcd_cmd(unsigned char value) {
    RS = 0;
    lcd_nibble(value >> 4);
    lcd_nibble(value & 0x0F);
    delay_ms(2);
}

void lcd_data(unsigned char value) {
    RS = 1;
    lcd_nibble(value >> 4);
    lcd_nibble(value & 0x0F);
    delay_ms(2);
}

void lcd_init() {
    RS = 0; EN = 0;
    delay_ms(20);
    lcd_nibble(0x03); delay_ms(5);
    lcd_nibble(0x03); delay_ms(1);
    lcd_nibble(0x03); delay_ms(1);
    lcd_nibble(0x02); delay_ms(1);
    
    lcd_cmd(0x28); // 4-bit, 2-line, 5x8 font
    lcd_cmd(0x0C); // Display ON, Cursor OFF
    lcd_cmd(0x06); // Auto-increment
    lcd_cmd(0x01); // Clear display
    delay_ms(5);
}

void lcd_puts(char *str) {
    while (*str) {
        lcd_data(*str);
        str++;
    }
}

void main() {
    lcd_init();
    lcd_puts("HI SIR!!");
    while (1);
}
```

---

## 4. Inference & Observations

1. **Pin Conservation via 4-Bit Mode**: Driving the LCD in 4-bit mode requires only 6 GPIO pins (`RS`, `EN`, `D4-D7`) compared to 10 pins in 8-bit mode, freeing Port 1 and Port 2 for other peripherals.
2. **Nibble Ordering**: The higher nibble (`value >> 4`) must be transmitted and latched via the `EN` strobe before the lower nibble (`value & 0x0F`).
3. **DDRAM Addressing**: Row 1 starts at address `0x80` (`0x80` to `0x8F`), while Row 2 starts at address `0xC0` (`0xC0` to `0xCF`), confirming cursor positioning behavior during keypad navigation.
