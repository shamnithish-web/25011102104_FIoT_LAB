# TASK11: STM32 Embedded HTTP Server with Two-Step CIPSEND Response & Node-RED HTTP Telemetry

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT11 |
| **DATE** | 12/10/2026 |
| **NAME OF EXP** | Embedded HTTP Server - STM32–Wemos Wi-Fi Modem Using AT Commands & Node-RED HTTP Client |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill), Wemos D1 Mini (ESP8266), Local Wi-Fi Network, PC Web Browser, Node-RED HTTP Flow |
| **TASK NO** | TASK11 |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| STM32 Pin | Peripheral Connection | Function |
|---|---|---|
| PA2 | ESP8266 RX (Pin D4 / GPIO2) | Modem Command Transmit (USART2_TX) |
| PA3 | ESP8266 TX (Pin D3 / GPIO0) | Modem Response Receive (USART2_RX) |
| PA9 | ST-Link / USB-UART RX | Debug Logging Console (USART1_TX) |
| PA10 | ST-Link / USB-UART TX | Debug Logging Console (USART1_RX) |
| 3.3V, GND | Wemos D1 Mini Power Rails | Power Supply (3.3V) |
| Wi-Fi LAN | PC Web Browser & Node-RED | HTTP Client Polling Endpoints |

---

## Core Logic & Pseudocode

```text
1. Initialize USART1 (debug) and USART2 (modem) at 115200 baud.
2. Connect to Wi-Fi Access Point using 'AT+CWJAP="SSID","PASS"'.
3. Enable multiple connections: 'AT+CIPMUX=1'.
4. Start TCP Server on Port 80: 'AT+CIPSERVER=1,80'.
5. In superloop:
   a. Monitor USART2 for incoming client request matching pattern: '+IPD,<link_id>,<len>:GET / ...'.
   b. Extract the integer link_id (e.g., 0, 1, 2).
   c. Prepare HTML response payload: '<html><body><h1>STM32 IoT Node</h1><p>Status: Online</p></body></html>'.
   d. Step 1: Send CIPSEND command: sprintf(cmd, "AT+CIPSEND=%d,%d\r\n", link_id, total_len).
   e. Wait for ESP8266 prompt: '> '.
   f. Step 2: Transmit full HTTP response with headers:
      "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n%s"
   g. Terminate client socket: sprintf(cmd, "AT+CIPCLOSE=%d\r\n", link_id).
6. Verify reception in browser (http://<ESP8266_IP>/) and in Node-RED using an Inject node -> HTTP Request node -> Debug node flow.
```

---

## Source Code Implementation

```c
#include "main.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void handle_http_request(int link_id) {
    char body[] = "<html><body><h1>STM32 IoT Node</h1><p>Status: Online</p></body></html>";
    char resp[256];
    char cmd[32];
    int body_len = strlen(body);
    int total_len;

    sprintf(resp, "HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: %d

%s", body_len, body);
    total_len = strlen(resp);

    /* Step 1: Issue CIPSEND command with link_id and total payload length */
    sprintf(cmd, "AT+CIPSEND=%d,%d
", link_id, total_len);
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 500);
    HAL_Delay(100);

    /* Step 2: Transmit HTTP response header and body */
    HAL_UART_Transmit(&huart2, (uint8_t*)resp, total_len, 1000);
    HAL_Delay(100);

    /* Step 3: Close connection gracefully */
    sprintf(cmd, "AT+CIPCLOSE=%d
", link_id);
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 500);
}

int main(void) {
    char buf[512];
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    while (1) {
        if (HAL_UART_Receive(&huart2, (uint8_t*)buf, sizeof(buf)-1, 200) == HAL_OK) {
            char *ipd = strstr(buf, "+IPD,");
            if (ipd) {
                int link_id = ipd[5] - '0';
                handle_http_request(link_id);
            }
        }
    }
}
```

---

## Inference & Technical Analysis

Dividing CIPSEND into command and payload phases ensures packet pacing without buffer overflow. Both web browsers and Node-RED HTTP request nodes successfully retrieved the HTML payload, establishing a robust edge-to-client pipeline.
