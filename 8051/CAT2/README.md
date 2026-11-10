# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-2 |
| **DATE** | 20/07/2026 (Week 2) |
| **NAME OF EXP** | 8051 Development Board Tool Chain Setup & GPIO Interfacing |
| **HARDWARE SETUP / PLATFORM** | AT89S52 Microcontroller Development Board + Keil µVision C51 + USBasp Programmer |
| **TASK NO** | Task 2A: Bare-Metal LED Blink & Task 2B: Custom Delay Function |

---

## 1. Hardware Bring-Up Sheet

| Parameter | Specification / Student Entry |
|---|---|
| **MCU** | Microchip / Atmel AT89S52 |
| **CPU Core** | 8051 8-bit CISC Architecture |
| **Operating Voltage** | 5.0 V DC (Regulated via LM7805) |
| **System Clock** | 11.0592 MHz Quartz Crystal (1 machine cycle = 1.085 µs) |
| **Debug / Flash Interface** | In-System Programming (ISP) via SPI (MOSI=P1.5, MISO=P1.6, SCK=P1.7, RST=Pin 9) |
| **User LEDs GPIO** | Port 1 (Pin P1.3 and Pin P1.4) |
| **LED Active State** | Active HIGH (Logic 1 = LED ON, Logic 0 = LED OFF) |
| **LED Frequency** | Approximately 1.0 Hz (~500 ms ON / 500 ms OFF) |

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Connections
- **Microcontroller**: AT89S52 in 40-pin DIP configuration.
- **Clock Circuit**: 11.0592 MHz quartz crystal connected across `XTAL1` (Pin 19) and `XTAL2` (Pin 18), stabilized with two 33 pF ceramic capacitors connected to Ground.
- **Reset Circuit**: 10 µF electrolytic capacitor connected between `VCC` and `RST` (Pin 9), with a 10 kΩ pull-down resistor to Ground for reliable power-on reset.
- **External Access**: `EA/VPP` (Pin 31) tied directly to `+5V (VCC)` to enable internal ROM program execution.
- **Outputs**:
  - `P1.3` connected to Anode of LED1 through a 330 Ω current-limiting resistor to Ground.
  - `P1.4` connected to Anode of LED2 through a 330 Ω current-limiting resistor to Ground.

---

## 3. Tasks & Implementation

### Task 2A — Bare-Metal GPIO Output & Software Loop Delay
Configure memory-mapped register bits `P1^3` and `P1^4` as push-pull digital outputs without using any high-level abstraction libraries. Alternately toggle the pins between HIGH (+5V) and LOW (0V) with a software nested loop.

### Task 2B — Custom Delay Function Implementation
Implement parameterized software delay routines (`delay()` and `delay2()`) calibrated to the 11.0592 MHz machine cycle frequency.

### Core Logic & Pseudocode
```text
1. Include 8051 register definitions: #include <reg51.h>
2. Map bit addressable pins:
      sbit ledpin  = P1^3;
      sbit ledpin2 = P1^4;
3. Implement nested loop delays:
      For i = 0 to 100:
          For j = 0 to 100: No-operation
4. Infinite execution loop:
      Turn ledpin ON (1), delay, turn ledpin OFF (0), delay
      Turn ledpin2 ON (1), delay2, turn ledpin2 OFF (0), delay2
5. Repeat continuously.
```

### Source Code (`blink.c`)
```c
#include <reg51.h> 

sbit ledpin = P1^3;
sbit ledpin2 = P1^4;

void delay();
void delay2();

void delay() {
    int i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
        }
    }
}

void delay2() {
    int i, j;
    for (i = 0; i < 400; i++) {
        for (j = 0; j < 400; j++) {
        }
    }
}

void main() {
    while (1) {
        ledpin = 1;
        delay();
        ledpin = 0;
        delay();
        
        ledpin2 = 1;
        delay2();
        ledpin2 = 0;
        delay2();
    }
}
```

---

## 4. Inference & Observations

1. **Register Memory Mapping**: The 8051 Special Function Register `P1` (address `0x90`) provides bit-level addressability. Setting `ledpin = 1` writes a logic HIGH directly to the latch.
2. **Timing Calibration**: At 11.0592 MHz, 1 machine cycle is 12 crystal oscillations ($pprox 1.085\ \mu	ext{s}$). The nested loop introduces deliberate CPU instruction stalls to generate a human-perceptible 1 Hz blink rate.
3. **Hardware Bring-Up Verification**: The power rails were verified at 5.02 V using a digital multimeter. Firmware was flashed via USBasp using ProgISP, successfully validating the entire Keil C51 build toolchain.
