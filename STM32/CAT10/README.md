# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-10 / 10C |
| **DATE** | 05/10/2026 & 12/10/2026 (Week 10) |
| **NAME OF EXP** | STM32–Wemos Wi-Fi Modem Interface Using AT Commands & HTTP Server |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 + Wemos D1 Mini (ESP8266) + Dual UART + Node-RED / Browser |
| **TASK NO** | Task 10A-B: AT Command Engine, Task 10C: TCP Server, Task 10D: HTTP Server, Task 10E: Node-RED |

---

## 1. Problem Statement

Develop an STM32-based HTTP sensor node in which the STM32 communicates with an ESP8266 / Wemos module through UART AT commands, configures the ESP8266 as a TCP server, receives an HTTP request through an `+IPD` frame, constructs an HTTP response, and transmits the response to a web browser and Node-RED client.

### Task Breakdown
- **Task 10A / 9A**: Establish dual UART communication between STM32, ESP8266, and host PC.
- **Task 10B / 9B**: Explore ESP8266 AT commands (`AT`, `AT+GMR`, `AT+CWMODE`, `AT+CWLAP`, `AT+CWJAP`, `AT+CIFSR`).
- **Task 10C**: Configure ESP8266 as a multi-connection TCP server on port 80 (`AT+CIPMUX=1`, `AT+CIPSERVER=1,80`).
- **Task 10D**: Parse the `+IPD` incoming frame and send the HTTP response in two steps via `AT+CIPSEND`.
- **Task 10E**: Configure Node-RED as a secondary HTTP polling client to display the node's webpage.

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Dual-UART Hardware Architecture
| Bus | STM32 Pin | Connected Device | Purpose |
|---|---|---|---|
| **USART2_TX** | `PA2` | Wemos D1 Mini `RX` (D4) | Sends AT commands to Wi-Fi modem |
| **USART2_RX** | `PA3` | Wemos D1 Mini `TX` (D3) | Receives modem responses and network data |
| **USART1_TX** | `PA9` | USB-to-TTL `RX` | Forwards debug logs to PC terminal |
| **USART1_RX** | `PA10` | USB-to-TTL `TX` | Receives operator console input |
| **Power** | `3.3V / 5V` | Wemos Power Rails | Common ground reference across boards |

---

## 3. Core Logic & AT Command Workflow

### HTTP Communication Sequence
```text
Browser / Node-RED              ESP8266                     STM32
       │                           │                          │
       │─── HTTP GET Request ─────>│                          │
       │                           │─── +IPD,0,len:GET / ────>│
       │                           │                          │ (Parse link_id=0)
       │                           │<── AT+CIPSEND=0,len ─────│
       │                           │─── > (Prompt) ──────────>│
       │                           │<── HTTP/1.1 200 OK... ───│
       │<── HTTP HTML Response ────│                          │
```

### Two-Step CIPSEND Construction
```c
// Step 1: Send CIPSEND command specifying link ID and total byte count
char cmd[32];
int body_len = strlen("<html><body><h1>STM32 IoT Node</h1></body></html>");
int resp_len = snprintf(response, sizeof(response),
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "<html><body><h1>STM32 IoT Node</h1></body></html>", body_len);

snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d,%d\r\n", link_id, resp_len);
HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 1000);

// Step 2: Wait for '>' prompt, then transmit the HTTP payload
HAL_UART_Receive(&huart2, &rx_char, 1, 2000);
if (rx_char == '>') {
    HAL_UART_Transmit(&huart2, (uint8_t*)response, resp_len, 2000);
}
```

---

## 4. Inference & Observations

1. **Dual-UART Architecture**: Dedicating `USART2` to the ESP8266 and `USART1` to the PC terminal enabled transparent debugging of raw AT commands without interfering with network communication.
2. **Buffer Frame Parsing**: The `+IPD,<id>,<len>:` frame identifies the active client connection ID, which is mandatory for routing the subsequent `AT+CIPSEND` response.
3. **Multi-Client Verification**: The STM32 server successfully served web pages simultaneously to a desktop Chrome browser and an automated Node-RED HTTP polling flow.
