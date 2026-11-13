# CAT13: BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics

## 1. Experiment Overview

| Field | Details |
|---|---|
| **Experiment Identifier** | CAT13 (Curriculum Ref: CAT12) |
| **Date of Execution** | 23/10/2026 |
| **Hardware Platform** | STM32 NUCLEO-F401RE + BME280 Environmental Sensor |
| **Curriculum Scope** | I2C1 bus communication, chip ID validation (0x60), raw register burst reading, and Bosch Sensortec API compensation. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Subtask Directory Index

| Subtask | Title | Description | Primary Peripherals |
|---|---|---|---|
| [TASK13A](TASK13A/README.md) | I2C Device Identification | Query register 0xD0 to confirm BME280 Chip ID (0x60). | I2C1 (PB8, PB9), BME280 |
| [TASK13B](TASK13B/README.md) | Raw Register Burst Reading | Multi-byte burst read of registers 0xF7 to 0xFE. | I2C1, BME280 Registers |
| [TASK13C](TASK13C/README.md) | Bosch Sensortec API Compensation | Integration of official Bosch API calibration formulas. | I2C1, Bosch bme280_dev |

---

## 4. Key Engineering Takeaways

1. **Precision Factory Calibration:** Raw 20-bit sensor ADC words require non-linear polynomial compensation using 24 factory trimming parameters.
2. **I2C Protocol Reliability:** Standard 100 kHz bus clocking with external pull-ups ensures robust environmental data capture.
