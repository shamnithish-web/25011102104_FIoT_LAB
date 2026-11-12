# TASK12B: BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 23/10/2026 |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE, BME280 Sensor, Bosch Sensortec Sensor API Driver Layer (bme280.h, bme280.c) |
| **TASK NO** | TASK12B |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | BME280 Pin | Function |
|---|---|---|
| PB8, PB9 | SCL, SDA | I2C1 Bus Interface |
| 3.3V, GND | VDD, GND | Sensor Power |

---

## Core Logic & Pseudocode

```text
1. Bind HAL I2C write/read functions to Bosch API function pointers:
   dev.read = user_i2c_read; dev.write = user_i2c_write; dev.delay_ms = user_delay_ms.
2. Call bme280_init(&dev) to parse factory calibration trimming parameters.
3. Configure oversampling: Osr_t=2x, Osr_p=16x, Osr_h=1x, Filter=16.
4. Set sensor mode to BME280_NORMAL_MODE.
5. In superloop:
   a. Call bme280_get_sensor_data(BME280_ALL, &comp_data, &dev).
   b. Print compensated Temperature (°C), Pressure (hPa), and Humidity (%RH).
   c. HAL_Delay(1000).
```

---

## Source Code Implementation

```c
#include "main.h"
#include "bme280.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;
struct bme280_dev dev;
struct bme280_data comp_data;

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr) {
    return HAL_I2C_Mem_Read(&hi2c1, (0x76 << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK ? BME280_OK : BME280_E_COMM_FAIL;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr) {
    return HAL_I2C_Mem_Write(&hi2c1, (0x76 << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)data, len, 1000) == HAL_OK ? BME280_OK : BME280_E_COMM_FAIL;
}

void user_delay_us(uint32_t period, void *intf_ptr) {
    HAL_Delay((period / 1000) + 1);
}

int main(void) {
    char out[128];
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;
    dev.intf = BME280_I2C_INTF;

    bme280_init(&dev);
    dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    dev.settings.filter = BME280_FILTER_COEFF_16;
    bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &dev);
    bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &dev);

    while (1) {
        bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
        sprintf(out, "Temp: %.2f C | Press: %.2f hPa | Hum: %.2f %%\r\n",
                comp_data.temperature, comp_data.pressure / 100.0, comp_data.humidity);
        HAL_UART_Transmit(&huart2, (uint8_t*)out, strlen(out), 500);
        HAL_Delay(1000);
    }
}
```

---

## Inference & Technical Analysis

Bosch Sensortec compensation algorithm applies non-linear polynomial corrections using factory calibration coefficients (dig_T1..T3, dig_P1..P9, dig_H1..H6) stored in sensor NVM, achieving high accuracy (±0.5°C, ±1 hPa, ±3% RH).
