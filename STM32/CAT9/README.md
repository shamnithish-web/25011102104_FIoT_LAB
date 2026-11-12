# CAT9: STM32 UART Command Controlled LED

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT9 |
| **Date of Execution** | 28/09/2026 |
| **Hardware Platform** | STM32 (ARM Cortex-M3) |
| **Curriculum Scope** | USART1 HAL driver bring-up, string transmission, and interactive character command parser. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Task ID | Folder Link | Description & Objective |
|---|---|---|
| **TASK9A** | [TASK9A](TASK9A/) | USART1 Serial Driver Bring-Up & Telemetry Banner Output |
| **TASK9B** | [TASK9B](TASK9B/) | Interactive UART Command Parser for LED Control |

---

## 4. Platform Specifications & Architecture

- **Microcontroller**: STM32 (ARM Cortex-M3)
- **Development Toolchain**: Keil C51 / Keil MDK-ARM with STM32CubeMX HAL Driver Layer.
- **Verification**: Complete source code, Keil project configurations, compiled `.hex` binaries, and circuit schematics are organized within each subtask directory.
