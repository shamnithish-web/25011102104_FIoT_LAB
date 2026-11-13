# Foundations of Internet of Things (FIoT) — Laboratory Repository

**Course:** 25CS2741 – Foundations of Internet of Things + Lab  
**Institution:** Shiv Nadar University – Chennai  
**Department:** Computer Science and Engineering  
**Student Name:** Sham Nithish  
**Registration Number:** 25011102104  
**Repository Name:** `25011102104_FIoT_LAB`  
**Target Hardware:** Intel/Atmel 8051 Microcontroller & STMicroelectronics STM32 (ARM Cortex-M3 / Cortex-M4)

---

## Laboratory Experiment Index & Verification Status

| Platform | Category | Experiment Name / Curriculum Title | Subtasks | Status |
|---|---|---|---|:---:|
| **8051** | **CAT2** | GPIO Interfacing & LED Blink Configuration | `TASK2B` | **PASSED** |
| **8051** | **CAT3** | Switch Input Polling & State Manipulation | `TASK3A` | **PASSED** |
| **8051** | **CAT4** | 4x4 Matrix Keypad Scanning & Seven-Segment Display Multiplexing | `TASK4A` | **PASSED** |
| **8051** | **CAT5** | Hardware Timer Configurations: Delays, PWM Generation & Event Counting | `TASK5A`, `TASK5B.1`, `TASK5B.2`, `TASK5B.3`, `TASK5C` | **PASSED** |
| **8051** | **CAT6** | UART Driver Architecture & Serial Communication Protocol | `TASK6A`, `TASK6B` | **PASSED** |
| **8051** | **CAT7** | External Hardware & Timer Interrupt Service Routines | `TASK7A`, `TASK7B`, `TASK7C` | **PASSED** |
| **STM32** | **CAT8** | STM32 GPIO Bring-up & Bi-directional Pin Manipulation | `TASK8A`, `TASK8B`, `TASK8C` | **PASSED** |
| **STM32** | **CAT9** | UART Serial Communication Driver & Command-Controlled LED | `TASK9A`, `TASK9B` | **PASSED** |
| **STM32** | **CAT10** | ESP8266 Modem Interface Using AT Commands & Multi-Connection TCP Server | `TASK10A`, `TASK10B` | **PASSED** |
| **STM32** | **CAT11** | Embedded HTTP Server - STM32–Wemos Wi-Fi Modem & Node-RED HTTP Client (10C) | `TASK11` | **PASSED** |
| **STM32** | **CAT12** | STM32F401RE Cortex-M4: GPIO and User Input Programming | `TASK12A`, `TASK12B` | **PASSED** |
| **STM32** | **CAT13** | BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics | `TASK13A`, `TASK13B`, `TASK13C` | **PASSED** |
| **STM32** | **CAT14** | BME280 Sensor Interfacing Using Custom Built ESP8266 API (ESPLib) | `TASK14` | **PASSED** |
| **STM32** | **CAT15** | Course Project: Smart IoT Environmental Node with MQTT & Node-RED Dashboard | `TASK15` | **PASSED** |

---

## Directory Architecture

```text
25011102104_FIoT_LAB/
├── .gitignore
├── README.md
├── 8051/
│   ├── CAT2/  (TASK2B: LED Blink)
│   ├── CAT3/  (TASK3A: Switch Polling)
│   ├── CAT4/  (TASK4A: 4x4 Keypad + 7-Segment)
│   ├── CAT5/  (TASK5A, TASK5B.1, TASK5B.2, TASK5B.3, TASK5C: Timers, PWM)
│   ├── CAT6/  (TASK6A, TASK6B: UART Serial Driver)
│   └── CAT7/  (TASK7A, TASK7B, TASK7C: Interrupts & LCD)
└── STM32/
    ├── CAT8/  (TASK8A, TASK8B, TASK8C: GPIO Blue Pill)
    ├── CAT9/  (TASK9A, TASK9B: UART Serial & Commands)
    ├── CAT10/ (TASK10A, TASK10B: ESP8266 Modem AT Commands & TCP Server)
    ├── CAT11/ (TASK11: 10C Embedded HTTP Server & Node-RED Client)
    ├── CAT12/ (TASK12A, TASK12B: Nucleo-F401RE GPIO & User Button B1)
    ├── CAT13/ (TASK13A, TASK13B, TASK13C: BME280 I2C & Bosch API)
    ├── CAT14/ (TASK14: BME280 Custom ESPLib Modem Driver)
    └── CAT15/ (TASK15: Course Project - BME280 + MQTT + Node-RED Dashboard)
```

---

## Build Tools & Verification Toolchain

- **8051 Keil C51 Compiler & µVision:** v5.38a
- **STM32CubeMX Configuration Tool:** v6.12.0
- **Keil MDK-ARM Cortex-M Toolchain:** v5.39
- **Firmware HAL Libraries:** STM32F1xx HAL v1.1.8 & STM32F4xx HAL v1.8.1
- **Node-RED Runtime:** v4.0+ with `@flowfuse/node-red-dashboard`
- **MQTT Broker:** `broker.emqx.io:1883` (Public Eclipse / EMQX Sandbox)
