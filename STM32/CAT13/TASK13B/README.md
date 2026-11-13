# TASK13B: Raw Temperature, Pressure & Humidity Burst Register Read

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT13 |
| **DATE** | 23/10/2026 |
| **NAME OF EXP** | Raw Temperature, Pressure & Humidity Burst Register Read |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE, BME280 Sensor Module |
| **TASK NO** | TASK13B |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Function |
|---|---|---|
| PB8, PB9 | BME280 I2C | Sensor Bus (I2C1) |
| PA2, PA3 | Serial Debug | Telemetry Console (USART2) |

---

## Core Logic & Pseudocode

```text
1. Configure BME280 oversampling: Pressure x1, Temp x1, Humidity x1.
2. Set normal mode (register 0xF4 = 0x27, 0xF2 = 0x01).
3. Issue 8-byte burst read starting at register 0xF7:
   - 0xF7..0xF9: Uncompensated Pressure (20-bit MSB, LSB, XLSB).
   - 0xFA..0xFC: Uncompensated Temperature (20-bit MSB, LSB, XLSB).
   - 0xFD..0xFE: Uncompensated Humidity (16-bit MSB, LSB).
4. Reconstruct raw integer words and print to debug console.
```

---

## Source Code Implementation

```c
#include "main.h"

I2C_HandleTypeDef hi2c1;

int main(void) {
    uint8_t raw_data[8];
    uint32_t raw_press, raw_temp;
    uint16_t raw_hum;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    while (1) {
        HAL_I2C_Mem_Read(&hi2c1, (0x76 << 1), 0xF7, I2C_MEMADD_SIZE_8BIT, raw_data, 8, 1000);
        raw_press = ((uint32_t)raw_data[0] << 12) | ((uint32_t)raw_data[1] << 4) | (raw_data[2] >> 4);
        raw_temp  = ((uint32_t)raw_data[3] << 12) | ((uint32_t)raw_data[4] << 4) | (raw_data[5] >> 4);
        raw_hum   = ((uint16_t)raw_data[6] << 8)  | raw_data[7];
        HAL_Delay(1000);
    }
}
```

---

## Inference & Technical Analysis

Performing an 8-byte contiguous burst read eliminates register synchronization discrepancies and ensures atomic timestamping across environmental channels.
