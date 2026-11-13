# TASK13A: I2C Device Identification & BME280 Chip ID Validation

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT13 |
| **DATE** | 23/10/2026 |
| **NAME OF EXP** | I2C Device Identification & BME280 Chip ID Validation |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE, BME280 Breakout Module (I2C: 0x76 / 0xEC) |
| **TASK NO** | TASK13A |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Function |
|---|---|---|
| PB8 | BME280 SCL | I2C1 Serial Clock |
| PB9 | BME280 SDA | I2C1 Serial Data |
| 3.3V, GND | BME280 VCC, GND | Power Supply (3.3V) |

---

## Core Logic & Pseudocode

```text
1. Initialize I2C1 in Standard Mode (100 kHz).
2. Query BME280 7-bit address 0x76 (shifted to 0xEC for HAL).
3. Read 1 byte from Register 0xD0 (BME280_CHIP_ID_ADDR).
4. Verify if received value equals 0x60.
5. If match, turn ON User LED (PA5); otherwise blink error pattern.
```

---

## Source Code Implementation

```c
#include "main.h"

I2C_HandleTypeDef hi2c1;

int main(void) {
    uint8_t chip_id = 0;
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    HAL_I2C_Mem_Read(&hi2c1, (0x76 << 1), 0xD0, I2C_MEMADD_SIZE_8BIT, &chip_id, 1, 1000);

    if (chip_id == 0x60) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }

    while (1) {
        HAL_Delay(100);
    }
}
```

---

## Inference & Technical Analysis

Validating the 0x60 Chip ID establishes proper I2C bus wiring and slave addressing before initiating data acquisition.
