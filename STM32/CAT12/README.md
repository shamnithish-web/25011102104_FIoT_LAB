# CAT12: STM32F401RE Cortex-M4: GPIO and User Input Programming

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT12 (Curriculum Ref: CAT11) |
| **Date of Execution** | 15/10/2026 |
| **Hardware Platform** | STM32 NUCLEO-F401RE (ARM Cortex-M4 @ 84 MHz) |
| **Curriculum Scope** | Nucleo-F401RE Cortex-M4 GPIO bring-up, User Button B1 polling, and software debouncing. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Subtask | Title | Description | Primary Peripherals |
|---|---|---|---|
| [TASK12A](TASK12A/README.md) | Nucleo User LED Toggle | 500 ms periodic toggle of on-board User LED LD2. | GPIOA (PA5), SystemTick |
| [TASK12B](TASK12B/README.md) | User Button B1 Polling & Debounce | Reading on-board pushbutton B1 with debouncing to toggle LED LD2 state. | GPIOC (PC13), GPIOA (PA5) |

---

## 4. Key Engineering Takeaways

1. **Cortex-M4 Architecture:** High-speed 84 MHz AHB/APB bus clocking enables deterministic sub-microsecond GPIO access.
2. **Debounce Filter:** 20 ms state-hold validation eliminates contact bounce glitches from physical pushbuttons.
