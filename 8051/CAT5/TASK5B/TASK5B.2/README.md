# TASK5B.2: Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT5 |
| **DATE** | 10/08/2026 |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 MCU, Indicator LED on P1.1 (via 330Ω), Timer 0 Timing Loop |
| **TASK NO** | TASK5B.2 |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| 8051 Pin | Connection | Function |
|---|---|---|
| Pin 2 (P1.1) | LED Anode via 330Ω to GND | 50% Duty Cycle PWM Output |

---

## Core Logic & Pseudocode

```text
1. Define PWM period T = 1000 µs (1 kHz carrier).
2. For 50% duty cycle: TON = 500 µs, TOFF = 500 µs.
3. In main loop:
   a. P1.1 = 1; delay_us(500).
   b. P1.1 = 0; delay_us(500).
```

---

## Source Code Implementation

```c
#include <reg51.h>

sbit PWM_PIN = P1^1;

void delay_10us(unsigned int count) {
    while(count--) {
        unsigned char k = 2;
        while(k--);
    }
}

void main() {
    while(1) {
        PWM_PIN = 1;
        delay_10us(50);  // 500us ON (50%)
        PWM_PIN = 0;
        delay_10us(50);  // 500us OFF (50%)
    }
}
```

---

## Inference & Technical Analysis

Average voltage output is V_avg = 0.50 * 5.0V = 2.50V, yielding moderate perceived brightness with balanced power dissipation across the current-limiting resistor.
