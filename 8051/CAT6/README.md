# CAT6: UART Driver and Serial Debugging

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT6 |
| **Date of Execution** | 17/08/2026 |
| **Hardware Platform** | 8051 (AT89S52) |
| **Curriculum Scope** | Timer 1 Mode 2 baud rate generation, asynchronous transmission, and full-duplex serial echo. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Task ID | Folder Link | Description & Objective |
|---|---|---|
| **TASK6A** | [TASK6A](TASK6A/) | UART Serial Transmitter: Telemetry String Output at 9600 Baud |
| **TASK6B** | [TASK6B](TASK6B/) | UART Full-Duplex Serial Echo & Receiver Controller |

---

## 4. Platform Specifications & Architecture

- **Microcontroller**: 8051 (AT89S52)
- **Development Toolchain**: Keil C51 / Keil MDK-ARM with STM32CubeMX HAL Driver Layer.
- **Verification**: Complete source code, Keil project configurations, compiled `.hex` binaries, and circuit schematics are organized within each subtask directory.
