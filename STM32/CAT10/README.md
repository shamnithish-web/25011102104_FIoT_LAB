# CAT10: STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT10 |
| **Date of Execution** | 05/10/2026 & 12/10/2026 |
| **Hardware Platform** | STM32 + ESP8266 |
| **Curriculum Scope** | ESP8266 AT command modem control, multi-connection TCP server on Port 80, and HTTP request parsing. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Task ID | Folder Link | Description & Objective |
|---|---|---|
| **TASK10A** | [TASK10A](TASK10A/) | ESP8266 Wi-Fi Modem Bring-Up & AT Command Verification |
| **TASK10B** | [TASK10B](TASK10B/) | ESP8266 TCP Multi-Connection Server Configuration (Port 80) |
| **TASK10C** | [TASK10C](TASK10C/) | Embedded HTTP Server Request Handling & Node-RED Integration |

---

## 4. Platform Specifications & Architecture

- **Microcontroller**: STM32 + ESP8266
- **Development Toolchain**: Keil C51 / Keil MDK-ARM with STM32CubeMX HAL Driver Layer.
- **Verification**: Complete source code, Keil project configurations, compiled `.hex` binaries, and circuit schematics are organized within each subtask directory.
