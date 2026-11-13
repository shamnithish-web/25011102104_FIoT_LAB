# CAT15: Course Project — Smart Environmental Monitoring Node with BME280, MQTT Cloud Uplink & Node-RED Dashboard

## 1. Project Overview

| Field | Details |
|---|---|
| **Course Project Identifier** | CAT15 (Curriculum Project Folder) |
| **Date of Execution** | 05/11/2026 |
| **Hardware Platform** | STM32 NUCLEO-F401RE (ARM Cortex-M4) + BME280 + ESP8266 |
| **Project Scope** | End-to-end IoT telemetry pipeline featuring BME280 precision acquisition, non-blocking MQTT client publishing to EMQX broker, and real-time visualization on a responsive Node-RED Dashboard. |

---

## 2. Hardware Circuit Diagram

![Circuit Diagram](circuit.png)

---

## 3. Node-RED Dashboard Live Telemetry

![Node-RED Dashboard Telemetry](dashboard.png)

---

## 4. Node-RED Telemetry Flow Architecture

![Node-RED Flow Architecture](nodered_flow.png)

---

## 5. Subtask Directory Index

| Subtask | Title | Description | Primary Peripherals |
|---|---|---|---|
| [TASK15](TASK15/README.md) | Smart IoT Environmental Monitoring Node | Complete production firmware, MQTT broker integration, and dashboard analytics. | I2C1, USART1, BME280, ESP8266, MQTT, Node-RED |

---

## 6. Key Engineering Achievements

1. **Precision Edge Sensing:** Industrial-grade temperature, pressure, and relative humidity acquisition calibrated via Bosch 64-bit polynomial compensation.
2. **Cloud MQTT Broker Link:** Lightweight MQTT packet framing publishing at 3-second intervals to `broker.emqx.io:1883` on topic `stm32/bme280/data`.
3. **Responsive Visual Analytics:** Low-latency Node-RED Dashboard featuring real-time gauges, time-series history charts, and connection health diagnostics.
