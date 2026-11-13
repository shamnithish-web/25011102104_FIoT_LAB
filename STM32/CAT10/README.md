# CAT10: STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Multi-Connection TCP Server

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT10 |
| **Date of Execution** | 05/10/2026 |
| **Hardware Platform** | STM32F103C8T6 + ESP8266 (Wemos D1 Mini) |
| **Curriculum Scope** | ESP8266 AT command modem control, AP association, IP configuration, and multi-connection TCP server on Port 80. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Subtask | Title | Description | Primary Peripherals |
|---|---|---|---|
| [TASK10A](TASK10A/README.md) | Modem Initialization & AP Association | Basic AT handshake, station mode configuration, and Wi-Fi network join. | USART1, USART2, ESP8266 |
| [TASK10B](TASK10B/README.md) | Multi-Connection TCP Server Setup | CIPMUX=1 and CIPSERVER=1,80 multi-client socket initialization. | USART2, ESP8266, TCP Socket |

---

## 4. Key Engineering Takeaways

1. **Hardware Handshaking:** Clean baud rate alignment at 115200 bps on USART2 is critical to avoid framing errors.
2. **Buffer Management:** Response parsing requires synchronous timeout windows to verify 'OK' status before issuing subsequent commands.
