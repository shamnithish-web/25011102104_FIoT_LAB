# CAT12: BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT12 |
| **Date of Execution** | 23/10/2026 |
| **Hardware Platform** | STM32 + BME280 |
| **Curriculum Scope** | I2C1 bus communication, Bosch Sensortec API compensation, and HTTP telemetry transmission to Node-RED. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Task ID | Folder Link | Description & Objective |
|---|---|---|
| **TASK12A** | [TASK12A](TASK12A/) | BME280 I2C Interface Bring-Up & Chip ID Verification |
| **TASK12B** | [TASK12B](TASK12B/) | Bosch Sensor API Calibration Readout & Environmental Data Acquisition |
| **TASK12C** | [TASK12C](TASK12C/) | STM32 BME280 Sensor Node HTTP REST Telemetry to Node-RED |

---

## 4. Platform Specifications & Architecture

- **Microcontroller**: STM32 + BME280
- **Development Toolchain**: Keil C51 / Keil MDK-ARM with STM32CubeMX HAL Driver Layer.
- **Verification**: Complete source code, Keil project configurations, compiled `.hex` binaries, and circuit schematics are organized within each subtask directory.
