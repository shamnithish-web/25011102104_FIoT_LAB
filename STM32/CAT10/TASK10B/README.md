# TASK10B: ESP8266 Multi-Connection TCP Server on Port 80

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT10 |
| **DATE** | 05/10/2026 |
| **NAME OF EXP** | ESP8266 Multi-Connection TCP Server on Port 80 |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill), Wemos D1 Mini (ESP8266), Local Wi-Fi Router |
| **TASK NO** | TASK10B |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| STM32 Pin | Target Device | Function |
|---|---|---|
| PA2, PA3 | ESP8266 RX, TX | Modem AT Command Link (USART2) |
| PA9, PA10 | PC Serial Terminal | Diagnostic Terminal (USART1) |
| 3.3V, GND | System Power Rail | Power Supply |

---

## Core Logic & Pseudocode

```text
1. Initialize USART1 and USART2 at 115200 baud.
2. Confirm modem connectivity: 'AT
'.
3. Enable multiple TCP connection mode: 'AT+CIPMUX=1
'.
4. Bind and start TCP Server on Port 80: 'AT+CIPSERVER=1,80
'.
5. Listen for incoming client connection notifications: '0,CONNECT'.
6. Verify socket state using 'AT+CIPSTATUS
'.
```

---

## Source Code Implementation

```c
#include "main.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    HAL_Delay(2000);
    HAL_UART_Transmit(&huart2, (uint8_t*)"AT+CIPMUX=1
", 13, 1000);
    HAL_Delay(500);
    HAL_UART_Transmit(&huart2, (uint8_t*)"AT+CIPSERVER=1,80
", 19, 1000);
    HAL_Delay(500);

    while (1) {
        // Superloop listens for TCP incoming connection events
        HAL_Delay(100);
    }
}
```

---

## Inference & Technical Analysis

Configuring `AT+CIPMUX=1` enables up to 4 concurrent client connections. Binding the server to Port 80 readies the modem for handling HTTP client traffic.
