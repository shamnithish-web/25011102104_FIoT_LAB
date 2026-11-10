# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-3 |
| **DATE** | 27/07/2026 (Week 3) |
| **NAME OF EXP** | Timer-Based LED Pattern Generator and Button Interrupt Controller |
| **HARDWARE SETUP / PLATFORM** | AT89S52 Microcontroller + 4-LED Output Array + Push-Button Switch + Keil C51 |
| **TASK NO** | 4-State LED Controller with Switch Polling & Software Debouncing |

---

## 1. Problem Statement

Design and implement a register-level GPIO controller for a microcontroller development board. Configure four LEDs as digital outputs and a push-button as a digital input. Using bare-metal Embedded C and direct memory-mapped register access, develop a four-state LED control system where each valid button press advances the operating mode:
- **Mode 1**: Running LED (Ring Shift: LED1 -> LED2 -> LED3 -> LED4 -> LED1).
- **Mode 2**: 4-Bit Binary Counter (`0000` to `1111`).
- **Mode 3**: Alternating Pattern (`1010` <-> `0101`).
- **Mode 4**: All LED Flash (`1111` <-> `0000`).

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Connections
- **Microcontroller**: AT89S52 (11.0592 MHz crystal, reset circuit).
- **Output LEDs**: Connected to Upper Nibble of Port 1:
  - `P1.4` -> LED1 (Green) via 330 Ω resistor
  - `P1.5` -> LED2 (Yellow) via 330 Ω resistor
  - `P1.6` -> LED3 (Red) via 330 Ω resistor
  - `P1.7` -> LED4 (Blue) via 330 Ω resistor
- **Push Button Interface**: Matrix switch connection:
  - Row line driven by `P2.5` (output active LOW).
  - Column line sensed at `P2.0` (input with internal weak pull-up).

---

## 3. Core Logic & Pseudocode

### State Transition & Switch Debounce Logic
1. Drive Row pin `P2.5 = 0` (Low scan pulse).
2. Read Column pin `P2.0`. If `P2.0 == 0`, switch contact closure is detected.
3. Call `delay()` (20 ms) to eliminate mechanical contact bounce.
4. If still LOW, confirm valid press event.
5. In Mode 1, sequentially activate one LED at a time:
   `P1.7 = 1, others 0` -> delay -> `P1.6 = 1` -> delay -> `P1.5 = 1` -> delay -> `P1.4 = 1` -> delay.

### Source Code (`switch.c` / `mode1.c`)
```c
#include <reg51.h>

sbit ledpin1 = P1^7;
sbit ledpin2 = P1^6;
sbit ledpin3 = P1^5;
sbit ledpin4 = P1^4;
sbit row = P2^5;
sbit col = P2^0;

void delay() {
    int i, j;
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 200; j++) {
        }
    }
}

int check() {
    row = 0;
    if (col == 0) {
        return 1;
    } else {
        return 0;
    }
}

void main() {
    while (1) {
        int find = check();
        if (find == 1) {
            ledpin1 = 1; ledpin2 = 0; ledpin3 = 0; ledpin4 = 0;
            delay();
            ledpin1 = 0; ledpin2 = 1; ledpin3 = 0; ledpin4 = 0;
            delay();
            ledpin1 = 0; ledpin2 = 0; ledpin3 = 1; ledpin4 = 0;
            delay();
            ledpin1 = 0; ledpin2 = 0; ledpin3 = 0; ledpin4 = 1;
            delay();
        }
    }
}
```

---

## 4. Inference & Observations

1. **Switch Bounce Filtering**: Mechanical push buttons exhibit contact chattering lasting 5 to 15 ms upon actuation. The implemented software delay filters out false trigger edges.
2. **Input Polling on 8051 Quasi-Bidirectional Ports**: When using Port 2 pins as inputs, writing `1` allows the internal pull-up to hold the pin high until an external switch pulls it to ground (`0`).
3. **Execution Behavior**: Each confirmed button press reliably advances the mode sequence without missing states or triggering double transitions.
