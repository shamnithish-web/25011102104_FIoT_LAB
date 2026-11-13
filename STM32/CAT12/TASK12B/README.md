# TASK12B: User Button B1 (PC13) Input Polling, Software Debounce & State Toggle

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 15/10/2026 |
| **NAME OF EXP** | User Button B1 (PC13) Input Polling, Software Debounce & State Toggle |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE Development Board |
| **TASK NO** | TASK12B |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Function |
|---|---|---|
| PC13 | On-board Blue Button (B1) | Input (Active Low) |
| PA5 | On-board Green LED (LD2) | Output Indicator |

---

## Core Logic & Pseudocode

```text
1. Configure PC13 as GPIO_MODE_INPUT with no pull (hardware pull-up present).
2. Configure PA5 as GPIO_MODE_OUTPUT_PP.
3. In superloop:
   a. Poll PC13: if HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET:
      - Delay 20 ms for contact debounce.
      - If still RESET, toggle PA5.
      - Wait while PC13 is held pressed (blocking release loop).
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
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
            HAL_Delay(20);
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
                HAL_Delay(20);
            }
        }
    }
}
```

---

## Inference & Technical Analysis

Integrating leading and trailing debounce delays effectively eliminates mechanical contact bounce, yielding a clean single LED toggle per button depression.
