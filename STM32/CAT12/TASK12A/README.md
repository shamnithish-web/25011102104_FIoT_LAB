# TASK12A: BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 23/10/2026 |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE, Bosch BME280 Combined Environmental Sensor, I2C1 (PB8=SCL, PB9=SDA, 100 kHz, 4.7kΩ pull-ups) |
| **TASK NO** | TASK12A |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | BME280 Pin | Function |
|---|---|---|
| PB8 | SCL | I2C1 Serial Clock Line |
| PB9 | SDA | I2C1 Serial Data Line |
| 3.3V | VDD / VDDIO | Sensor Power (+3.3V DC) |
| GND | GND | Common Reference Ground |
| GND / 3.3V | SDO / ADDR | I2C Address Select (0x76 / 0x77) |

---

## Core Logic & Pseudocode

```text
1. Configure I2C1 in standard mode (100 kHz).
2. Transmit read command to Register 0xD0 (BME280_CHIP_ID_ADDR).
3. Read 1 byte into chip_id variable.
4. Verify: if chip_id == 0x60 (BME280) or 0x58 (BMP280):
   Print 'BME280 Detected Successfully'.
5. Else: Print 'Sensor Detection Error'.
```

---

## Source Code Implementation

```c
#include "main.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

int main(void) {
    uint8_t chip_id = 0;
    char msg[64];
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    // Read Chip ID from BME280 (Address 0x76 << 1 = 0xEC)
    HAL_I2C_Mem_Read(&hi2c1, (0x76 << 1), 0xD0, I2C_MEMADD_SIZE_8BIT, &chip_id, 1, 1000);

    sprintf(msg, "BME280 Chip ID Read: 0x%02X\r\n", chip_id);
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 500);

    while (1) {
        HAL_Delay(1000);
    }
}
```

---

## Inference & Technical Analysis

Register 0xD0 contains the fixed identification code (0x60 for BME280, 0x58 for BMP280). Successful bus transactions validate pull-up sizing and I2C address resolution.
