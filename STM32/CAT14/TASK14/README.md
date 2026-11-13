# TASK14: Modular Hardware Abstraction Driver (ESPLib) for Embedded Wi-Fi Modem Interfacing

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT14 |
| **DATE** | 29/10/2026 |
| **NAME OF EXP** | BME280 Sensor Interfacing Using Custom Built ESP8266 API (ESPLib) |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE, BME280 Sensor, ESP8266 Wi-Fi Modem |
| **TASK NO** | TASK14 |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Function |
|---|---|---|
| PB8, PB9 | BME280 Module | I2C Sensor Acquisition |
| PA9, PA10 | ESP8266 Modem | USART1 Modem Driver Interface |
| 3.3V, GND | Power Bus | System Power Rail |

---

## Core Logic & Pseudocode

```text
1. Initialize Nucleo-F401RE clock, I2C1, and USART1.
2. Initialize BME280 sensor structure using Bosch API.
3. Call ESP_Init(&huart1) to initialize modem driver state machine.
4. Issue high-level API call: ESP_ConnectAP("SSID", "PASS").
5. In superloop:
   a. Read calibrated environmental metrics from BME280.
   b. Construct telemetry string: "TEMP: 26.4 C, HUM: 58.2 %".
   c. Issue high-level API call: ESP_SendTCP(payload).
   d. Delay 2000 ms.
```

---

## Source Code Implementation

```c
#include "main.h"
#include "bme280.h"
#include "ESPLib.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;
struct bme280_data sensor_data;

int main(void) {
    char tele_buf[128];
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    ESP_Init(&huart1);
    ESP_JoinAP("iPhone", "rith1100");

    while (1) {
        bme280_get_sensor_data(BME280_ALL, &sensor_data, &dev);
        sprintf(tele_buf, "T:%.2f H:%.2f P:%.2f", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure);
        ESP_SendPacket(tele_buf);
        HAL_Delay(2000);
    }
}
```

---

## Inference & Technical Analysis

Modular driver architecture (ESPLib) decouples low-level UART AT framing from top-level application logic, significantly improving testability and code maintainability.
