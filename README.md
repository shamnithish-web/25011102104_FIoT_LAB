# 25011102104_FIoT_LAB – Fundamentals of Internet of Things Laboratory Repository

## 1. Student & Course Information

| Field | Details |
|---|---|
| **Student Name** | Sham Nithish |
| **Registration Number** | 25011102104 |
| **Degree & Branch** | B.Tech. Computer Science & Engineering (IoT) |
| **Year / Semester** | II Year / III Semester |
| **Course Code** | 25CS2741 |
| **Course Name** | Fundamentals of Internet of Things + Lab |
| **Repository Name** | `25011102104_FIoT_LAB` |

---

## 2. About This Repository

This repository contains the complete laboratory submissions for **25CS2741 Fundamentals of Internet of Things + Lab**. The curriculum spans register-level bare-metal programming on the **8051 (AT89S52)** microcontroller family and HAL-driven embedded systems development on **STM32 (ARM Cortex-M3 / Cortex-M4)** platforms, culminating in wireless IoT telemetry via **ESP8266 Wi-Fi** using **HTTP REST** and **MQTT** integrated with **Node-RED**.

Every experiment is structured according to the official automated evaluation specification:
1. **Experiment Metadata & Official Problem Statement** (CAT Identifier, Date, Official Title, Hardware Setup, Task Numbers).
2. **Circuit Schematic Diagram** (`circuit.png`) detailing microcontroller pinouts, clock oscillators, power connections, and peripheral interfaces.
3. **Subtask Folders** (`TASK...`) for each subdivision containing dedicated Keil projects, C source code, startup files, and compiled `.hex` binaries.
4. **Core Logic, Algorithms, and Pseudocode**.
5. **Engineering Inferences and Observations**.

---

## 3. Master Index of Laboratory Experiments (CAT2 – CAT14)

### Platform 1: 8051 Microcontroller (AT89S52)

| CAT ID | Week | Date | Official Experiment Title | Subtasks | Hardware Setup | CAT Folder |
|---|---|---|---|---|---|---|
| **CAT2** | Week 2 | 20/07/2026 | 8051 Development Board Tool Chain Setup & GPIO Interfacing | [TASK2B](./8051/CAT2/TASK2B/) | AT89S52, 11.0592 MHz XTAL, LEDs (P1.3, P1.4), Keil C51 | [8051/CAT2/](./8051/CAT2/) |
| **CAT3** | Week 3 | 27/07/2026 | Timer-Based LED Pattern Generator and Button Interrupt Controller (Switch Polling) | [TASK3A](./8051/CAT3/TASK3A/) | AT89S52, 4-bit LED Array (P1.4-P1.7), Push Button (P2.0) | [8051/CAT3/](./8051/CAT3/) |
| **CAT4** | Week 4 | 03/08/2026 | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display | [TASK4A](./8051/CAT4/TASK4A/) | AT89S52, 4x4 Keypad (Port 2), 7-Segment (Port 0), LEDs | [8051/CAT4/](./8051/CAT4/) |
| **CAT5** | Week 5 | 10/08/2026 | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | [TASK5A](./8051/CAT5/TASK5A/), [TASK5B.1](./8051/CAT5/TASK5B/TASK5B.1/), [TASK5B.2](./8051/CAT5/TASK5B/TASK5B.2/), [TASK5B.3](./8051/CAT5/TASK5B/TASK5B.3/), [TASK5C](./8051/CAT5/TASK5C/) | AT89S52, Timer 0 Mode 1, PWM LED (P1.1), ULN2003 Stepper Driver | [8051/CAT5/](./8051/CAT5/) |
| **CAT6** | Week 6 | 17/08/2026 | UART Driver and Serial Debugging | [TASK6A](./8051/CAT6/TASK6A/), [TASK6B](./8051/CAT6/TASK6B/) | AT89S52, Timer 1 Mode 2, USB-to-TTL UART (P3.0/P3.1), PuTTY | [8051/CAT6/](./8051/CAT6/) |
| **CAT7** | Week 7 | 24/08/2026 | 16x2 LCD Driver Development and Dynamic Display Control | [TASK7A](./8051/CAT7/TASK7A/), [TASK7B](./8051/CAT7/TASK7B/), [TASK7C](./8051/CAT7/TASK7C/) | AT89S52, HD44780 16x2 LCD (4-bit Mode), 4x4 Keypad | [8051/CAT7/](./8051/CAT7/) |

---

### Platform 2: STM32 Microcontrollers (ARM Cortex-M3 & Cortex-M4)

| CAT ID | Week | Date | Official Experiment Title | Subtasks | Hardware Setup | CAT Folder |
|---|---|---|---|---|---|---|
| **CAT8** | Week 8 | 18/09/2026 | STM32 GPIO Bring-Up and Switch-Controlled LED | [TASK8A](./STM32/CAT8/TASK8A/), [TASK8B](./STM32/CAT8/TASK8B/), [TASK8C](./STM32/CAT8/TASK8C/) | STM32F103C8T6 (Blue Pill), On-board LED (PC13), Button (PA12) | [STM32/CAT8/](./STM32/CAT8/) |
| **CAT9** | Week 9 | 28/09/2026 | STM32 UART Command Controlled LED | [TASK9A](./STM32/CAT9/TASK9A/), [TASK9B](./STM32/CAT9/TASK9B/) | STM32F103C8T6, USART1 (PA9/PA10), USB-TTL Bridge, PuTTY | [STM32/CAT9/](./STM32/CAT9/) |
| **CAT10** | Week 10 | 05/10/2026 & 12/10/2026 | STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server | [TASK10A](./STM32/CAT10/TASK10A/), [TASK10B](./STM32/CAT10/TASK10B/), [TASK10C](./STM32/CAT10/TASK10C/) | STM32F103C8T6, Wemos D1 Mini (ESP8266), USART1/2, Node-RED | [STM32/CAT10/](./STM32/CAT10/) |
| **CAT11** | Week 11 | 14/10/2026 | STM32F401RE Cortex-M4: GPIO and User Input Programming | [TASK11A](./STM32/CAT11/TASK11A/), [TASK11B](./STM32/CAT11/TASK11B/) | STM32 NUCLEO-F401RE, User LED LD2 (PA5), User Button B1 (PC13) | [STM32/CAT11/](./STM32/CAT11/) |
| **CAT12** | Week 12 | 23/10/2026 | BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics | [TASK12A](./STM32/CAT12/TASK12A/), [TASK12B](./STM32/CAT12/TASK12B/), [TASK12C](./STM32/CAT12/TASK12C/) | STM32F401RE Nucleo, BME280 (I2C1), ESP8266 Wi-Fi, Node-RED | [STM32/CAT12/](./STM32/CAT12/) |
| **CAT13** | Week 13 | 27/10/2026 | BME280 Sensor Interfacing Using Custom Built ESP8266 API | [TASK13](./STM32/CAT13/TASK13/) | STM32F401RE Nucleo, BME280 (I2C1), Custom ESPLib Driver | [STM32/CAT13/](./STM32/CAT13/) |
| **CAT14** | Week 14 | 04/11/2026 | BME280 Sensor Interfacing Using MQTT Cloud Publishing & Node-RED Analytics | [TASK14](./STM32/CAT14/TASK14/) | STM32F401RE Nucleo, BME280, ESP8266, EMQX MQTT, Node-RED | [STM32/CAT14/](./STM32/CAT14/) |

---

## 4. Master Task Directory Matrix (All 28 Tasks)

| # | Task Path | Experiment Title | Hardware Platform | Documentation |
|---|---|---|---|---|
| 1 | `8051/CAT2/TASK2B` | GPIO LED Blinking & Alternating Output | AT89S52 (Port 1) | [README.md](./8051/CAT2/TASK2B/README.md) |
| 2 | `8051/CAT3/TASK3A` | Switch Polling & Multi-Mode Pattern Generator | AT89S52 (Port 1 & P2.0) | [README.md](./8051/CAT3/TASK3A/README.md) |
| 3 | `8051/CAT4/TASK4A` | 4x4 Matrix Keypad to 7-Segment Hex Display | AT89S52 (Port 0 & Port 2) | [README.md](./8051/CAT4/TASK4A/README.md) |
| 4 | `8051/CAT5/TASK5A` | Hardware Timer 0 Mode 1: 1 kHz Square Wave | AT89S52 (Timer 0) | [README.md](./8051/CAT5/TASK5A/README.md) |
| 5 | `8051/CAT5/TASK5B/TASK5B.1` | Software PWM LED Dimming (25% Duty Cycle) | AT89S52 (P1.1) | [README.md](./8051/CAT5/TASK5B/TASK5B.1/README.md) |
| 6 | `8051/CAT5/TASK5B/TASK5B.2` | Software PWM LED Dimming (50% Duty Cycle) | AT89S52 (P1.1) | [README.md](./8051/CAT5/TASK5B/TASK5B.2/README.md) |
| 7 | `8051/CAT5/TASK5B/TASK5B.3` | Software PWM LED Dimming (75% Duty Cycle) | AT89S52 (P1.1) | [README.md](./8051/CAT5/TASK5B/TASK5B.3/README.md) |
| 8 | `8051/CAT5/TASK5C` | Stepper Motor Control via ULN2003 Driver | AT89S52 (P1.4-P1.7) | [README.md](./8051/CAT5/TASK5C/README.md) |
| 9 | `8051/CAT6/TASK6A` | UART Serial String Transmission at 9600 Baud | AT89S52 (Timer 1, P3.1) | [README.md](./8051/CAT6/TASK6A/README.md) |
| 10 | `8051/CAT6/TASK6B` | UART Full-Duplex Serial Echo Controller | AT89S52 (P3.0, P3.1) | [README.md](./8051/CAT6/TASK6B/README.md) |
| 11 | `8051/CAT7/TASK7A` | 16x2 LCD 4-Bit Driver Initialization & Text | AT89S52 (Port 2) | [README.md](./8051/CAT7/TASK7A/README.md) |
| 12 | `8051/CAT7/TASK7B` | 16x2 LCD Dynamic Marquee Text Scrolling | AT89S52 (Port 2) | [README.md](./8051/CAT7/TASK7B/README.md) |
| 13 | `8051/CAT7/TASK7C` | 4x4 Matrix Keypad Input to 16x2 LCD Display | AT89S52 (Port 0 & Port 2) | [README.md](./8051/CAT7/TASK7C/README.md) |
| 14 | `STM32/CAT8/TASK8A` | On-board User LED (PC13) Bring-Up & 1 Hz Blink | STM32F103C8T6 (Blue Pill) | [README.md](./STM32/CAT8/TASK8A/README.md) |
| 15 | `STM32/CAT8/TASK8B` | External GPIO Output Driving & Alternating Pattern | STM32F103C8T6 (PB0, PC13) | [README.md](./STM32/CAT8/TASK8B/README.md) |
| 16 | `STM32/CAT8/TASK8C` | Push-Button Switch (PA12) Input Polling & Toggle | STM32F103C8T6 (PA12, PC13) | [README.md](./STM32/CAT8/TASK8C/README.md) |
| 17 | `STM32/CAT9/TASK9A` | USART1 Serial Transmitter & Telemetry Banner | STM32F103C8T6 (PA9/PA10) | [README.md](./STM32/CAT9/TASK9A/README.md) |
| 18 | `STM32/CAT9/TASK9B` | Interactive UART Command Parser for LED Control | STM32F103C8T6 (USART1) | [README.md](./STM32/CAT9/TASK9B/README.md) |
| 19 | `STM32/CAT10/TASK10A` | ESP8266 Modem Bring-Up & AT Command Verification | STM32F103 + ESP8266 | [README.md](./STM32/CAT10/TASK10A/README.md) |
| 20 | `STM32/CAT10/TASK10B` | ESP8266 TCP Multi-Connection Server Config (Port 80) | STM32F103 + ESP8266 | [README.md](./STM32/CAT10/TASK10B/README.md) |
| 21 | `STM32/CAT10/TASK10C` | Embedded HTTP Server Request Handling & Node-RED | STM32F103 + ESP8266 | [README.md](./STM32/CAT10/TASK10C/README.md) |
| 22 | `STM32/CAT11/TASK11A` | Nucleo-F401RE User Button B1 Polling & LD2 LED | STM32F401RE Nucleo | [README.md](./STM32/CAT11/TASK11A/README.md) |
| 23 | `STM32/CAT11/TASK11B` | Multi-State Button Timing (Short vs. Long Press) | STM32F401RE Nucleo | [README.md](./STM32/CAT11/TASK11B/README.md) |
| 24 | `STM32/CAT12/TASK12A` | BME280 I2C Interface Bring-Up & Chip ID Verification | STM32F401RE + BME280 | [README.md](./STM32/CAT12/TASK12A/README.md) |
| 25 | `STM32/CAT12/TASK12B` | Bosch Sensor API Calibration & Environmental Acquisition | STM32F401RE + BME280 | [README.md](./STM32/CAT12/TASK12B/README.md) |
| 26 | `STM32/CAT12/TASK12C` | BME280 HTTP REST Telemetry Response to Node-RED | STM32F401RE + BME280 + ESP | [README.md](./STM32/CAT12/TASK12C/README.md) |
| 27 | `STM32/CAT13/TASK13` | Modular STM32 Sensor Node with ESPLib Wi-Fi Driver | STM32F401RE + BME280 + ESP | [README.md](./STM32/CAT13/TASK13/README.md) |
| 28 | `STM32/CAT14/TASK14` | MQTT Cloud Telemetry Node Publishing to EMQX & Node-RED | STM32F401RE + BME280 + MQTT | [README.md](./STM32/CAT14/TASK14/README.md) |

---

## 5. Repository Directory Structure

```text
25011102104_FIoT_LAB/
│
├── .gitignore                      # Excludes intermediate object/build files while preserving .hex
├── README.md                       # Master Laboratory Documentation & Index Matrix
│
├── 8051/                           # 8051 Microcontroller (AT89S52) Platform Experiments
│   ├── CAT2/                       # Tool Chain Setup & GPIO Interfacing
│   │   ├── README.md
│   │   ├── circuit.png
│   │   └── TASK2B/
│   │       ├── README.md, circuit.png, blink.c, led.uvproj, STARTUP.A51, Objects/led.hex
│   ├── CAT3/                       # Switch Polling & Multi-Mode Pattern Generator
│   │   ├── README.md
│   │   ├── circuit.png
│   │   └── TASK3A/
│   │       ├── README.md, circuit.png, switch.c, switch1.uvproj, STARTUP.A51, Objects/switch1.hex
│   ├── CAT4/                       # 4x4 Keypad + 7-Segment Display
│   │   ├── README.md
│   │   ├── circuit.png
│   │   └── TASK4A/
│   │       ├── README.md, circuit.png, segment.c, 7segment.uvproj, STARTUP.A51, Objects/7segment.hex
│   ├── CAT5/                       # Hardware Timer 0, Software PWM & Stepper Motor
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK5A/                 # Timer 0 Square Wave (1 kHz)
│   │   ├── TASK5B/
│   │   │   ├── TASK5B.1/           # PWM Dimming (25% Duty Cycle)
│   │   │   ├── TASK5B.2/           # PWM Dimming (50% Duty Cycle)
│   │   │   └── TASK5B.3/           # PWM Dimming (75% Duty Cycle)
│   │   └── TASK5C/                 # 4-Phase Stepper Motor Control via ULN2003
│   ├── CAT6/                       # UART Serial Driver & Debugging
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── TASK6A/                 # UART Serial String Transmission at 9600 Baud
│   │   └── TASK6B/                 # UART Full-Duplex Serial Echo Controller
│   └── CAT7/                       # 16x2 HD44780 LCD Driver Development
│       ├── README.md
│       ├── circuit.png
│       ├── TASK7A/                 # 16x2 LCD 4-Bit Driver Initialization & Text Display
│       ├── TASK7B/                 # Dynamic Marquee Display Scrolling & Text Rotation
│       └── TASK7C/                 # Matrix Keypad Entry to 16x2 LCD Display
│
└── STM32/                          # STM32 ARM Cortex-M Platform Experiments
    ├── CAT8/                       # STM32 GPIO Bring-Up & Switch-Controlled LED
    │   ├── README.md, circuit.png
    │   ├── TASK8A/                 # On-board LED PC13 Blink (.ioc, Core/, Drivers/, MDK-ARM/)
    │   ├── TASK8B/                 # External LED Drive (.ioc, Core/, Drivers/, MDK-ARM/)
    │   └── TASK8C/                 # Push Button PA12 Polling (.ioc, Core/, Drivers/, MDK-ARM/)
    ├── CAT9/                       # UART Command Controlled LED
    │   ├── README.md, circuit.png
    │   ├── TASK9A/                 # USART1 Driver Bring-Up (.ioc, Core/, Drivers/, MDK-ARM/)
    │   └── TASK9B/                 # Interactive Command Parser (.ioc, Core/, Drivers/, MDK-ARM/)
    ├── CAT10/                      # ESP8266 Modem AT Commands & Embedded HTTP Server
    │   ├── README.md, circuit.png
    │   ├── TASK10A/                # ESP8266 Modem Bring-Up & AT Commands (.ioc, Core/, Drivers/, MDK-ARM/)
    │   ├── TASK10B/                # TCP Server Config on Port 80 (.ioc, Core/, Drivers/, MDK-ARM/)
    │   └── TASK10C/                # Embedded HTTP Server & Node-RED (.ioc, Core/, Drivers/, MDK-ARM/)
    ├── CAT11/                      # Nucleo-F401RE GPIO & User Input
    │   ├── README.md, circuit.png
    │   ├── TASK11A/                # User Button B1 Polling & User LED LD2 (.ioc, Core/, Drivers/, MDK-ARM/)
    │   └── TASK11B/                # Multi-State Button Timing (Short vs. Long Press)
    ├── CAT12/                      # BME280 Sensor I2C & Bosch Sensor API + HTTP Analytics
    │   ├── README.md, circuit.png
    │   ├── TASK12A/                # BME280 I2C Bring-Up & Chip ID Verification (.ioc, Core/, Drivers/, MDK-ARM/)
    │   ├── TASK12B/                # Bosch Sensor API Compensation Readout (.ioc, Core/, Drivers/, MDK-ARM/)
    │   └── TASK12C/                # BME280 HTTP REST Telemetry to Node-RED (.ioc, Core/, Drivers/, MDK-ARM/)
    ├── CAT13/                      # BME280 Sensor Interfacing Using Custom Built ESP8266 API
    │   ├── README.md, circuit.png
    │   └── TASK13/                 # Modular STM32 Sensor Node with ESPLib Driver (.ioc, Core/, Drivers/, MDK-ARM/)
    └── CAT14/                      # BME280 Sensor Interfacing Using MQTT Cloud Publishing
        ├── README.md, circuit.png
        └── TASK14/                 # MQTT Cloud Telemetry Node to EMQX & Node-RED (.ioc, Core/, Drivers/, MDK-ARM/)
```

---

## 6. Toolchains & Development Environments

1. **8051 Microcontroller Development**:
   - **IDE**: Keil µVision C51 (v9.61)
   - **Target**: AT89S52 (40-pin DIP, 8 KB Flash, 256 bytes RAM)
   - **Programmer**: USBasp / ProgISP v1.72
   - **C Compiler**: Keil C51 ANSI C Cross-Compiler

2. **STM32 Development**:
   - **IDE & Toolchain**: Keil MDK-ARM (v5.x) / Arm Compiler 5/6
   - **Hardware Configuration**: STM32CubeMX (v6.x) with HAL Driver Layer
   - **Target MCUs**:
     - STM32F103C8T6 (ARM Cortex-M3, 72 MHz, 64 KB Flash, 20 KB SRAM)
     - STM32F401RET6 (ARM Cortex-M4 with FPU, 84 MHz, 512 KB Flash, 96 KB SRAM)
   - **Hardware Debugger**: ST-LINK / V2-1 on-board Nucleo SWD

3. **IoT Networking & Cloud Telemetry**:
   - **Wi-Fi Transceiver**: Wemos D1 Mini / ESP8266 (Espressif AT firmware v1.7+)
   - **Protocols**: UART AT Commands, TCP/IP, HTTP REST, MQTT (`broker.emqx.io:1883`)
   - **IoT Dashboard & Analytics**: Node-RED local and cloud telemetry flows
