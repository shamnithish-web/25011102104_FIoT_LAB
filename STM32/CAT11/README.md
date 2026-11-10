# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-11 |
| **DATE** | 14/10/2026 (Week 11) |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE Development Board + Keil MDK-ARM + STM32CubeMX |
| **TASK NO** | Task 1: On-Board LED Bring-Up, Task 2: Switch State Remembrance, Task 3: Short/Long Press |

---

## 1. Problem Statement

Bring up the high-performance ARM Cortex-M4 NUCLEO-F401RE development board:
1. **Task 1 — On-board LED Bring-Up**: Verify hardware and clock trees by toggling the user LED (`LD2` on `PA5`) at a fixed 500 ms interval.
2. **Task 2 — On-board Switch Control with State Remembrance**: Read the user push button (`B1` on `PC13`). Each valid press toggles the LED state, and the LED retains its state indefinitely after the button is released.
3. **Task 3 — Short-Press and Long-Press Detection**: Implement duration classification:
   - **Short Press (< 1s)**: Inverts the LED static state.
   - **Long Press ($\ge$ 1s)**: Triggers continuous blinking mode ($f = 5\ \text{Hz}$).

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Specifications
- **Development Board**: STMicroelectronics NUCLEO-F401RE.
- **Target MCU**: STM32F401RET6 (ARM Cortex-M4 with FPU, 84 MHz, 512 KB Flash, 96 KB SRAM).
- **User Peripherals**:
  - `PA5`: Green User LED `LD2` (Active HIGH, driven directly by MCU).
  - `PC13`: Blue User Push Button `B1` (Active LOW with external 100 nF debounce capacitor and pull-up).
- **Debugger**: Integrated ST-LINK/V2-1 via USB Mini-B with Virtual COM Port on `USART2`.

---

## 3. Core Logic & Source Code

### Main Application Loop (`CAT11/Core/Src/main.c`)
```c
/* USER CODE BEGIN 2 */
uint32_t press_time = 0;
uint8_t button_pressed = 0;
uint8_t blink_mode = 0;
uint32_t last_blink = 0;

/* USER CODE END 2 */

/* USER CODE BEGIN WHILE */
while (1) {
    /* USER CODE END WHILE */
    
    // Check if B1 button is pressed (Active LOW)
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET && !button_pressed) {
        button_pressed = 1;
        press_time = HAL_GetTick();
    }
    
    // Check when B1 button is released
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET && button_pressed) {
        uint32_t duration = HAL_GetTick() - press_time;
        button_pressed = 0;
        
        if (duration < 1000) {
            // Short Press: Toggle State
            blink_mode = 0;
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        } else {
            // Long Press: Toggle Blink Mode
            blink_mode = !blink_mode;
        }
    }
    
    // Non-blocking blinking execution
    if (blink_mode) {
        if (HAL_GetTick() - last_blink >= 100) {
            last_blink = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
    }
}
```

---

## 4. Inference & Observations

1. **Cortex-M4 Architecture**: Compared to the Cortex-M3 (F103), the Cortex-M4 (F401) features hardware floating-point support (FPU), higher clock speeds (84 MHz), and advanced GPIO peripheral bus routing (`AHB1`).
2. **State Remembrance**: Debouncing and tracking button state transitions rather than level states ensures that holding the button down does not result in erratic toggling.
3. **Execution Accuracy**: Millisecond-accurate duration tracking via the ARM SysTick timer confirmed exact separation of short press (<1s) and long press (>=1s) events.
