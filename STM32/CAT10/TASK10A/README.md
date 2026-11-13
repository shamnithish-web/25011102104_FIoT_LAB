# TASK10A: ESP8266 Modem Initialization, Access Point Association & IP Query

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT10 |
| **DATE** | 05/10/2026 |
| **NAME OF EXP** | ESP8266 Modem Initialization, Access Point Association & IP Query |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill), Wemos D1 Mini (ESP8266), USB-UART Debug Console |
| **TASK NO** | TASK10A |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| STM32 Pin | Peripheral Connection | Function |
|---|---|---|
| PA9 | USB-UART RX (ST-Link / CP2102) | Debug Serial Print (USART1_TX) |
| PA10 | USB-UART TX (ST-Link / CP2102) | Debug Serial Receive (USART1_RX) |
| PA2 | ESP8266 RX (Pin D4 / GPIO2) | Modem Command Transmit (USART2_TX) |
| PA3 | ESP8266 TX (Pin D3 / GPIO0) | Modem Response Receive (USART2_RX) |
| 3.3V, GND | Wemos D1 Mini Power Rails | Power Supply |

---

## Core Logic & Pseudocode

```text
1. Initialize USART1 (115200 bps, 8N1) for diagnostic output.
2. Initialize USART2 (115200 bps, 8N1) for modem communication.
3. Transmit basic ping: 'AT
' and await 'OK'.
4. Set Wi-Fi operation to Station Mode: 'AT+CWMODE=1
'.
5. Connect to local Wireless Access Point: 'AT+CWJAP="SSID","PASSWORD"
'.
6. Verify connection status and query assigned IP: 'AT+CIFSR
'.
7. Print obtained IP and MAC address to USART1 console.
```

---

## Source Code Implementation

```c
#include "main.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void send_cmd(char *cmd) {
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 1000);
    HAL_Delay(100);
}

int main(void) {
    char rx_buf[256];
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    HAL_Delay(2000);
    send_cmd("AT
");
    HAL_Delay(500);
    send_cmd("AT+CWMODE=1
");
    HAL_Delay(500);
    send_cmd("AT+CWJAP="iPhone","rith1100"
");
    HAL_Delay(4000);
    send_cmd("AT+CIFSR
");

    while (1) {
        if (HAL_UART_Receive(&huart2, (uint8_t*)rx_buf, sizeof(rx_buf)-1, 100) == HAL_OK) {
            HAL_UART_Transmit(&huart1, (uint8_t*)rx_buf, strlen(rx_buf), 100);
        }
    }
}
```

---

## Inference & Technical Analysis

The ESP8266 modem reliably responds with `WIFI CONNECTED` and `WIFI GOT IP` upon receiving valid credentials. Station mode ensures the STM32 operates as an IP endpoint on the local LAN.
