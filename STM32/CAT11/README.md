# CAT11: Embedded HTTP Server - STM32–Wemos Wi-Fi Modem Using AT Commands & Node-RED HTTP Client

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT11 (Curriculum Ref: CAT10C) |
| **Date of Execution** | 12/10/2026 |
| **Hardware Platform** | STM32F103C8T6 + ESP8266 (Wemos D1 Mini) |
| **Curriculum Scope** | Processing incoming +IPD frames, executing two-step CIPSEND transmissions, hosting an embedded HTTP web server, and servicing Node-RED HTTP client polling. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Subtask | Title | Description | Primary Peripherals |
|---|---|---|---|
| [TASK11](TASK11/README.md) | Embedded HTTP Server & Node-RED Integration | +IPD parsing, two-step CIPSEND response assembly, and dual-client support (browser & Node-RED). | USART1, USART2, ESP8266, HTTP/1.1 |

---

## 4. Key Engineering Takeaways

1. **Two-Step Transmission:** Dividing data transfer into command phase (`AT+CIPSEND=<id>,<len>`) and payload phase avoids buffer truncation.
2. **REST / HTTP Compatibility:** Node-RED HTTP request nodes can poll the STM32 web server periodically to extract sensor status or control actuators.
