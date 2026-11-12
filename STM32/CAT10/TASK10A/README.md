# TASK10A: STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT10 |
| **DATE** | 05/10/2026 |
| **NAME OF EXP** | STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6, Wemos D1 Mini (ESP8266), USART1 (PC Debug), USART2 (PA2=TX, PA3=RX to ESP8266) |
| **TASK NO** | TASK10A |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| STM32 Pin | ESP8266 Pin | Function |
|---|---|---|
| PA2 (USART2_TX) | ESP8266 RX (via 3.3V) | AT Command Transmission |
| PA3 (USART2_RX) | ESP8266 TX | Modem Response Reception |
| PA9, PA10 | PC Serial Terminal | Diagnostic Monitor (115200 baud) |
| GND | GND | Common Reference Ground |

---

## Core Logic & Pseudocode

```text
1. Configure USART1 (115200) for PC logging and USART2 (115200) for ESP8266 modem.
2. Send AT synchronization: 'AT\r\n'.
3. Wait for 'OK' in modem response.
4. Set Wi-Fi Station Mode: 'AT+CWMODE=1\r\n'.
5. Wait for 'OK'.
6. Forward modem response to PC diagnostic console.
```

---

## Source Code Implementation

```c
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void send_at(char *cmd) {
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 500);
}

int main(void) {
    char rx_buf[128];
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    HAL_Delay(2000); // Modem power-up delay
    send_at("AT\r\n");
    HAL_UART_Receive(&huart2, (uint8_t*)rx_buf, sizeof(rx_buf)-1, 1000);
    HAL_UART_Transmit(&huart1, (uint8_t*)rx_buf, strlen(rx_buf), 500);

    send_at("AT+CWMODE=1\r\n");
    HAL_UART_Receive(&huart2, (uint8_t*)rx_buf, sizeof(rx_buf)-1, 1000);
    HAL_UART_Transmit(&huart1, (uint8_t*)rx_buf, strlen(rx_buf), 500);

    while (1) {
        HAL_Delay(1000);
    }
}
```

---

## Inference & Technical Analysis

Standard Espressif AT firmware acts as a network coprocessor over UART, offloading 802.11 b/g/n PHY, WPA2 encryption, and TCP/IP stack execution from the STM32 Cortex-M3 microcontroller.
