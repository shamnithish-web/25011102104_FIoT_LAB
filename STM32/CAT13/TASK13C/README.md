# TASK13C: Bosch Sensortec API Integration & Floating-Point Sensor Compensation

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT13 |
| **DATE** | 23/10/2026 |
| **NAME OF EXP** | Bosch Sensortec API Integration & Floating-Point Sensor Compensation |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE, BME280 Environmental Sensor |
| **TASK NO** | TASK13C |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Function |
|---|---|---|
| PB8, PB9 | BME280 I2C | Sensor Bus (I2C1) |
| Internal | FPU (Cortex-M4) | Hardware Floating Point Unit |

---

## Core Logic & Pseudocode

```text
1. Link Bosch 'bme280.c' driver into project.
2. Implement platform I2C read/write wrapper callbacks.
3. Call bme280_init(&dev) to retrieve trimming parameters.
4. Configure sensor mode to BME280_NORMAL_MODE.
5. In superloop:
   a. Call bme280_get_sensor_data(BME280_ALL, &comp_data, &dev).
   b. Extract compensated temperature (deg C), pressure (hPa), humidity (% RH).
   c. Print calibrated metrics to serial console.
```

---

## Source Code Implementation

```c
#include "main.h"
#include "bme280.h"

struct bme280_dev dev;
struct bme280_data comp_data;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;
    bme280_init(&dev);

    while (1) {
        bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
        HAL_Delay(1000);
    }
}
```

---

## Inference & Technical Analysis

Bosch API compensation yields high-accuracy ambient telemetry with 0.01°C temperature and 0.18 hPa pressure resolution.
