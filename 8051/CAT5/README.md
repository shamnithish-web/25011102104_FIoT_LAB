# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-5 |
| **DATE** | 10/08/2026 (Week 5) |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 + Timer 0 (Mode 1) + PWM LED + ULN2003 Stepper Motor Driver |
| **TASK NO** | Task 1: 1s Hardware Timer Timebase, Task 2: Software PWM LED Fading, Task 3: Stepper Motor Control |

---

## 1. Problem Statement

Design a timer-driven embedded control system using the 8051 in which a hardware timer periodically generates interrupts to:
1. Provide a precise non-blocking 1-second system timebase.
2. Control LED brightness using software Pulse Width Modulation (PWM) at 500 Hz – 1 kHz.
3. Generate variable-frequency pulse signals (100 Hz, 500 Hz, 1 kHz, 2 kHz).
4. Drive the stepping sequence of a 4-phase unipolar stepper motor.

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Mathematical Derivation of Timer 0 Reload Values
- **Crystal Frequency ($f_{	ext{osc}}$)**: 11.0592 MHz
- **Machine Cycle Period**:
  $$T_{	ext{machine}} = \frac{12}{f_{	ext{osc}}} = \frac{12}{11.0592 \times 10^6} \approx 1.08507\ \mu\text{s}$$
- **For a 1 ms interrupt period**:
  $$N_{	ext{counts}} = \frac{1\ \text{ms}}{1.08507\ \mu\text{s}} \approx 922\ \text{counts}$$
- **16-Bit Timer Reload Value**:
  $$\text{Preload} = 65536 - 922 = 64614 = \text{0xFC66}$$
  $$\text{TH0} = \text{0xFC},\quad \text{TL0} = \text{0x66}$$

---

## 3. Core Logic & Source Code

### Timer 0 Initialization & Periodic LED Toggling (`timer.c`)
```c
#include <reg51.h>

sbit led = P1^1;
int count = 0;

void main() {
    TMOD = 0x01;    // Timer 0 in Mode 1 (16-bit timer)
    TH0 = 0xEA;     // Preload values for periodic overflow
    TL0 = 0x66;
    TR0 = 1;        // Start Timer 0

    while (1) {
        if (TF0 == 1) {     // Check overflow flag
            TH0 = 0xEA;
            TL0 = 0x66;
            TF0 = 0;        // Clear overflow flag
            count++;
            if (count > 133) { // Calibrated to 1 second interval
                led = !led;
                count = 0;
            }
        }
    }
}
```

### Software PWM Fading Algorithm
- **Frequency**: 500 Hz (Period $T = 2\ \text{ms}$).
- **Duty Cycle Range**: 0% to 100% in 100 steps.
- **Modulation**: During each PWM cycle, the pin is driven HIGH for $D\%$ of the period and LOW for the remaining $(100 - D)\%$. Incrementing $D$ produces smooth fading without visible flickering.

### Stepper Motor Commutation Sequence
A 4-phase unipolar stepper motor driven by ULN2003 on pins `P1.4` - `P1.7`:
- Step 1: `1000` (`0x80`)
- Step 2: `0100` (`0x40`)
- Step 3: `0010` (`0x20`)
- Step 4: `0001` (`0x10`)
- Speed is controlled by varying the inter-step timer interrupt interval (Slow: 100 ms/step, Medium: 50 ms/step, Fast: 10 ms/step).

---

## 4. Inference & Observations

1. **Precision of Hardware Timers**: Unlike software nested loops which block the CPU and vary with compiler optimization, hardware timer interrupts run concurrently in hardware, providing deterministic, jitter-free timing.
2. **PWM Persistence of Vision (PoV)**: At PWM frequencies $\ge 500\ \text{Hz}$, the human eye integrates the light pulses, perceiving duty cycle changes as linear brightness variation.
3. **Stepper Driver Isolation**: The ULN2003 Darlington transistor array successfully sinks up to 500 mA per channel, protecting the microcontroller from inductive flyback voltage spikes.
