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

This repository contains the complete laboratory submissions for **25CS2741 Fundamentals of Internet of Things + Lab**. The coursework spans bare-metal register-level programming on the **8051 (AT89S52)** microcontroller family and HAL-driven embedded systems development on **STM32 (ARM Cortex-M3 / Cortex-M4)** platforms, culminating in wireless IoT telemetry via **ESP8266 Wi-Fi** using **HTTP REST** and **MQTT** integrated with **Node-RED**.

Every experiment contains:
1. **Prescribed Experiment Details** (CAT Identifier, Date, Official Experiment Title, Hardware Setup).
2. **Circuit Schematic Diagram** (`circuit.png`) detailing microcontroller pinouts, clock oscillators, power connections, and peripheral interfaces.
3. **Task Subdivisions** (`TASKA`, `TASKB`, etc.) following official laboratory problem statements.
4. **Core Logic, Algorithms, and Pseudocode**.
5. **Verified Source Code & IDE Project Files** (Keil C51 `.uvproj`, Keil MDK-ARM `.uvprojx`, STM32CubeMX `.ioc`, and compiled `.hex` firmware).
6. **Engineering Inferences and Observations**.

---

## 3. Master Index of Laboratory Experiments

### Platform 1: 8051 Microcontroller (AT89S52)

| CAT ID | Week | Date | Official Experiment Title | Hardware Setup | Task Folder |
|---|---|---|---|---|---|
| **CAT2** | Week 2 | 20/07/2026 | 8051 Development Board Tool Chain Setup & GPIO Interfacing | AT89S52, 11.0592 MHz XTAL, LEDs (P1.3, P1.4), Keil C51 | [8051/CAT2/](./8051/CAT2/) |
| **CAT3** | Week 3 | 27/07/2026 | Timer-Based LED Pattern Generator and Button Interrupt Controller (Switch Polling) | AT89S52, 4-bit LED Array (P1.4-P1.7), Push Button (P2.5/P2.0) | [8051/CAT3/](./8051/CAT3/) |
| **CAT4** | Week 4 | 03/08/2026 | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display | AT89S52, 4x4 Keypad (Port 2), 7-Segment (Port 0), LEDs (Port 1) | [8051/CAT4/](./8051/CAT4/) |
| **CAT5** | Week 5 | 10/08/2026 | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | AT89S52, Timer 0 Mode 1, PWM LED (P1.1), ULN2003 Stepper Driver | [8051/CAT5/](./8051/CAT5/) |
| **CAT6** | Week 6 | 17/08/2026 | UART Driver and Serial Debugging | AT89S52, Timer 1 Mode 2, USB-to-TTL UART (P3.0/P3.1), PuTTY | [8051/CAT6/](./8051/CAT6/) |
| **CAT7** | Week 7 | 24/08/2026 | 16x2 LCD Driver Development and Dynamic Display Control | AT89S52, HD44780 16x2 LCD (4-bit Mode), 4x4 Matrix Keypad | [8051/CAT7/](./8051/CAT7/) |

### Platform 2: STM32 Microcontrollers (ARM Cortex-M3 & Cortex-M4)

| CAT ID | Week | Date | Official Experiment Title | Hardware Setup | Task Folder |
|---|---|---|---|---|---|
| **CAT8** | Week 8 | 18/09/2026 | STM32 GPIO Bring-Up and Switch-Controlled LED | STM32F103C8T6 (Blue Pill), On-board LED (PC13), Button (PA12) | [STM32/CAT8/](./STM32/CAT8/) |
| **CAT9** | Week 9 | 28/09/2026 | STM32 UART Command Controlled LED | STM32F103C8T6, USART1 (PA9/PA10), USB-TTL Bridge, PuTTY | [STM32/CAT9/](./STM32/CAT9/) |
| **CAT10** | Week 10 | 05/10/2026 & 12/10/2026 | STM32–Wemos Wi-Fi Modem Interface Using AT Commands & HTTP Server | STM32F103C8T6, Wemos D1 Mini (ESP8266), USART1/2, Node-RED | [STM32/CAT10/](./STM32/CAT10/) |
| **CAT11** | Week 11 | 14/10/2026 | STM32F401RE Cortex-M4: GPIO and User Input Programming | STM32 NUCLEO-F401RE, User LED (PA5), User Button B1 (PC13) | [STM32/CAT11/](./STM32/CAT11/) |
| **CAT12** | Week 12 | 23/10/2026 | BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics | STM32F401RE Nucleo, BME280 (I2C1), ESP8266 Wi-Fi, Node-RED | [STM32/CAT12/](./STM32/CAT12/) |
| **CAT13** | Week 13 | 27/10/2026 | BME280 Sensor Interfacing Using I2C and (MQTT) using Custom Built ESP8266 API - Node Analytics | STM32F401RE Nucleo, BME280, ESP8266, EMQX MQTT, Node-RED | [STM32/CAT13/](./STM32/CAT13/) |

---

## 4. Repository Directory Structure

```text
25011102104_FIoT_LAB/
│
├── .gitignore                      # Configured to ignore listings/intermediates, tracking .hex
├── README.md                       # Master Laboratory Documentation & Index
│
├── 8051/                           # 8051 Microcontroller (AT89S52) Experiments
│   ├── CAT2/                       # Tool Chain Setup & Bare-Metal GPIO LED Blink
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── blink.c
│   │   ├── led.uvproj
│   │   ├── STARTUP.A51
│   │   └── Objects/led.hex
│   ├── CAT3/                       # Switch Polling & Multi-Mode Pattern Generator
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── switch.c
│   │   ├── mode1.c
│   │   ├── switch1.uvproj
│   │   ├── STARTUP.A51
│   │   └── Objects/switch1.hex
│   ├── CAT4/                       # 4x4 Keypad + 7-Segment Display + Status LEDs
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── segment.c
│   │   ├── 7segment.uvproj
│   │   ├── STARTUP.A51
│   │   └── Objects/7segment.hex
│   ├── CAT5/                       # Hardware Timer 0 Interrupt, Software PWM & Stepper
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── timer.c
│   │   ├── hardware.uvproj
│   │   ├── STARTUP.A51
│   │   └── Objects/hardware.hex
│   ├── CAT6/                       # Full-Duplex UART Serial Communication & Echo
│   │   ├── README.md
│   │   ├── circuit.png
│   │   ├── uart.c
│   │   ├── UART.uvproj
│   │   ├── STARTUP.A51
│   │   └── Objects/UART.hex
│   └── CAT7/                       # 16x2 HD44780 LCD Driver (4-Bit Mode) & Keypad Nav
│       ├── README.md
│       ├── circuit.png
│       ├── LCD.c
│       ├── lcd2.c
│       ├── 7thlab.uvproj
│       ├── practice.uvproj
│       ├── STARTUP.A51
│       └── Objects/7thlab.hex
│
└── STM32/                          # STM32 ARM Cortex-M Platform Experiments
    ├── CAT8/                       # STM32 GPIO Bring-Up & Switch-Controlled LED
    │   ├── README.md
    │   ├── circuit.png
    │   ├── cat8.ioc
    │   ├── 8B.ioc
    │   ├── Core/Inc/
    │   ├── Core/Src/main.c
    │   ├── Drivers/
    │   └── MDK-ARM/
    ├── CAT9/                       # UART Command Controlled LED & Serial Parsing
    │   ├── README.md
    │   ├── circuit.png
    │   ├── CAT9.ioc
    │   ├── Core/Inc/
    │   ├── Core/Src/main.c
    │   ├── Drivers/
    │   └── MDK-ARM/
    ├── CAT10/                      # ESP8266 Modem AT Commands & Embedded HTTP Server
    │   ├── README.md
    │   ├── circuit.png
    │   ├── CAT10A.ioc
    │   ├── Core/Inc/
    │   ├── Core/Src/main.c
    │   ├── Drivers/
    │   └── MDK-ARM/
    ├── CAT11/                      # Nucleo-F401RE GPIO Bring-Up & Short/Long Press
    │   ├── README.md
    │   ├── circuit.png
    │   ├── CAT11.ioc
    │   ├── Core/Inc/
    │   ├── Core/Src/main.c
    │   ├── Drivers/
    │   └── MDK-ARM/
    ├── CAT12/                      # BME280 I2C Bosch Sensor API & HTTP to Node-RED
    │   ├── README.md
    │   ├── circuit.png
    │   ├── CAT12.ioc
    │   ├── SENSOR.ioc
    │   ├── Core/Inc/bme280.h
    │   ├── Core/Inc/bme280_defs.h
    │   ├── Core/Src/bme280.c
    │   ├── Core/Src/main.c
    │   ├── Drivers/
    │   └── MDK-ARM/
    └── CAT13/                      # BME280 Sensor & MQTT Cloud Publishing (Node-RED)
        ├── README.md
        ├── circuit.png
        ├── CAT13.ioc
        ├── project.ioc
        ├── Core/Inc/ESPLib.h
        ├── Core/Inc/bme280.h
        ├── Core/Src/ESPLib.c
        ├── Core/Src/bme280.c
        ├── Core/Src/main.c
        ├── Drivers/
        └── MDK-ARM/
```

---

## 5. Toolchains & Development Environments

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
   - **Protocols**: UART AT Commands, TCP/IP, HTTP REST, MQTT (broker.emqx.io:1883)
   - **IoT Dashboard & Analytics**: Node-RED local runtime
