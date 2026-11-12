# TASK10B: STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT10 |
| **DATE** | 05/10/2026 |
| **NAME OF EXP** | STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6, Wemos D1 Mini (ESP8266), Local Wi-Fi Router Access Point |
| **TASK NO** | TASK10B |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| STM32 Pin | ESP8266 Pin | Function |
|---|---|---|
| PA2, PA3 | RX, TX | UART2 Modem Bridge |
| 3.3V, GND | 3.3V, GND | Power Supply Rail |

---

## Core Logic & Pseudocode

```text
1. Initialize UART1 (Debug) and UART2 (Modem).
2. Connect to Wi-Fi Access Point: 'AT+CWJAP="SSID","PASS"\r\n'.
3. Wait for 'WIFI CONNECTED' and 'WIFI GOT IP'.
4. Query IP address: 'AT+CIFSR\r\n'.
5. Enable multiple TCP connections: 'AT+CIPMUX=1\r\n'.
6. Start TCP Server on Port 80: 'AT+CIPSERVER=1,80\r\n'.
7. Verify server start confirmation.
```

---

## Source Code Implementation

```c
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void esp_exec(char *cmd, uint32_t timeout) {
    char buf[256] = {0};
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), timeout);
    HAL_UART_Receive(&huart2, (uint8_t*)buf, sizeof(buf)-1, timeout);
    HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 500);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    HAL_Delay(2000);
    esp_exec("AT\r\n", 500);
    esp_exec("AT+CIPMUX=1\r\n", 500);
    esp_exec("AT+CIPSERVER=1,80\r\n", 1000);

    while (1) {
        HAL_Delay(1000);
    }
}
```

---

## Inference & Technical Analysis

AT+CIPMUX=1 enables the ESP8266 socket multiplexer for up to 5 concurrent TCP client connections (channel IDs 0-4). Opening TCP server on port 80 allows any HTTP web browser or Node-RED node to initiate connections.
