# CAT14: BME280 Sensor Interfacing Using Custom Built ESP8266 API (ESPLib)

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT14 (Curriculum Ref: CAT13) |
| **Date of Execution** | 29/10/2026 |
| **Hardware Platform** | STM32 NUCLEO-F401RE + BME280 + ESP8266 |
| **Curriculum Scope** | Modular hardware abstraction driver architecture (ESPLib) for embedded Wi-Fi modem interfacing and non-blocking command execution. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Subtask | Title | Description | Primary Peripherals |
|---|---|---|---|
| [TASK14](TASK14/README.md) | ESPLib Modular Driver Architecture | Layered driver wrapping AT commands into high-level C function primitives. | USART1, I2C1, BME280, ESP8266 |

---

## 4. Key Engineering Takeaways

1. **Abstraction Decoupling:** Isolating modem UART transactions behind function APIs (`ESP_Init`, `ESP_Send`) improves software portability.
2. **State Verification:** Built-in error handling guards against wireless network disconnects.
