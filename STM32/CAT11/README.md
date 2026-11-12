# CAT11: STM32F401RE Cortex-M4: GPIO and User Input Programming

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT11 |
| **Date of Execution** | 14/10/2026 |
| **Hardware Platform** | STM32 (ARM Cortex-M4) |
| **Curriculum Scope** | Nucleo-F401RE Cortex-M4 GPIO bring-up, User Button B1 polling, and short vs. long press detection. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Task ID | Folder Link | Description & Objective |
|---|---|---|
| **TASK11A** | [TASK11A](TASK11A/) | Nucleo-F401RE User Button B1 (PC13) Polling & User LED LD2 Control |
| **TASK11B** | [TASK11B](TASK11B/) | Multi-State Button Timing: Short Press vs. Long Press Mode Discrimination |

---

## 4. Platform Specifications & Architecture

- **Microcontroller**: STM32 (ARM Cortex-M4)
- **Development Toolchain**: Keil C51 / Keil MDK-ARM with STM32CubeMX HAL Driver Layer.
- **Verification**: Complete source code, Keil project configurations, compiled `.hex` binaries, and circuit schematics are organized within each subtask directory.
