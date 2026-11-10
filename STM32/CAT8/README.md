# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-8 |
| **DATE** | 18/09/2026 (Week 8) |
| **NAME OF EXP** | STM32 GPIO Bring-Up and Switch-Controlled LED |
| **HARDWARE SETUP / PLATFORM** | STM32 Blue Pill (STM32F103C8T6 ARM Cortex-M3) + Keil MDK-ARM + STM32CubeMX |
| **TASK NO** | Task 8A: GPIO Output, Task 8B: Event-Based Toggle, Task 8C: Short/Long Press |

---

## 1. Problem Statement

Bring up the STM32F103C8T6 microcontroller board using STM32CubeMX and the STM32 HAL library:
1. **Task 8A — GPIO Input/Output**: Interface an on-board LED (`PC13`) and an external push button (`PA12`). The LED follows the switch state directly.
2. **Task 8B — Event-Based Control**: Toggle the LED upon a validated switch press with software debouncing.
3. **Task 8C — Short Press vs Long Press**: Classify button press duration non-blockingly using `HAL_GetTick()`:
   - **Short Press (< 1s)**: Toggle LED state once.
   - **Long Press ($\ge$ 1s)**: Enter continuous blinking mode until next press.

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Connections
- **Microcontroller**: STM32F103C8T6 (72 MHz max, 64 KB Flash, 20 KB SRAM).
- **On-board User LED**: Connected to pin `PC13`.
  - Configured as **GPIO Output (Push-Pull, Low speed)**.
  - Active-LOW circuit: Writing `GPIO_PIN_RESET` turns the LED ON; writing `GPIO_PIN_SET` turns the LED OFF.
- **Push Button Input**: Connected to pin `PA12`.
  - Configured as **GPIO Input with internal pull-up / external 10 kΩ pull-up**.
  - Pressed = `GPIO_PIN_RESET` (GND), Released = `GPIO_PIN_SET` (+3.3V).
- **Clock**: 8.000 MHz HSE crystal oscillator multiplied via PLL to 72 MHz.

---

## 3. Core Logic & Pseudocode

### Core HAL Functions Used
| HAL Function | Purpose |
|---|---|
| `HAL_GPIO_ReadPin()` | Read digital input state from PA12 |
| `HAL_GPIO_WritePin()` | Drive PC13 high or low |
| `HAL_GPIO_TogglePin()` | Invert state of PC13 |
| `HAL_GetTick()` | Returns millisecond count since system boot |

### Implementation Code (`Core/Src/main.c`)
```c
/* USER CODE BEGIN WHILE */
while (1) {
    /* USER CODE END WHILE */
    
    // Task 8A & 8B: Debounced Event Toggle
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET) {
        HAL_Delay(20); // Software debounce
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET); // Wait for release
        }
    }
}
```

### Non-Blocking Short/Long Press Classification Algorithm
```text
1. When PA12 transitions from HIGH to LOW:
      Record press_start_time = HAL_GetTick()
2. When PA12 transitions from LOW to HIGH:
      duration = HAL_GetTick() - press_start_time
      If duration < 1000 ms:
          Execute Short Press: HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)
      Else:
          Execute Long Press: Toggle continuous_blink_mode flag
3. If continuous_blink_mode == TRUE:
      Non-blocking blink: if (HAL_GetTick() - last_blink >= 250) Toggle PC13
```

---

## 4. Inference & Observations

1. **Active-LOW Electrical Polarity**: The Blue Pill's onboard LED cathode is tied to `PC13` while the anode is connected to `3.3V` via a current-limiting resistor. Hence, driving the pin LOW sinks current and illuminates the LED.
2. **Non-Blocking Architecture**: Using `HAL_GetTick()` eliminates CPU blocking caused by `HAL_Delay()`, allowing the microcontroller to handle concurrent events, timers, and serial comms without stalling.
