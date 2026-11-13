# TASK12A: Nucleo-F401RE User LED (PA5) Blinking & Clock Configuration

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 15/10/2026 |
| **NAME OF EXP** | Nucleo-F401RE User LED (PA5) Blinking & Clock Configuration |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE Development Board (ARM Cortex-M4) |
| **TASK NO** | TASK12A |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Function |
|---|---|---|
| PA5 | On-board Green LED (LD2) | Output Indicator |
| Internal | SysTick Timer | 1 ms Time Base |

---

## Core Logic & Pseudocode

```text
1. Initialize HAL and configure system clock to 84 MHz.
2. Enable GPIOA peripheral clock: __HAL_RCC_GPIOA_CLK_ENABLE().
3. Configure PA5 in GPIO_MODE_OUTPUT_PP, no pull, speed LOW.
4. In superloop:
   a. Toggle PA5: HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5).
   b. Delay 500 ms: HAL_Delay(500).
```

---

## Source Code Implementation

```c
#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
}
```

---

## Inference & Technical Analysis

The Cortex-M4 core executes single-cycle port manipulation via peripheral bit-banding, verifying proper board bring-up.
