# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-4 |
| **DATE** | 03/08/2026 (Week 4) |
| **NAME OF EXP** | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display |
| **HARDWARE SETUP / PLATFORM** | AT89S52 + 4x4 Matrix Keypad + 7-Segment Display + Status LEDs + Keil C51 |
| **TASK NO** | Keypad-Driven Multi-Peripheral HMI Controller |

---

## 1. Problem Statement

Design an embedded user interface where a 4x4 keypad acts as an input device, a seven-segment display provides visual feedback of the active digit, and an array of LEDs indicates operating modes.

### Functional Requirements Table
| Key Press | Seven-Segment Display | LED Operation |
|---|---|---|
| **1** | `1` | LED1 ON |
| **2** | `2` | LED2 ON |
| **3** | `3` | LED3 ON |
| **4** | `4` | LED4 ON |
| **5** | `5` | Running LED Pattern |
| **6** | `6` | Alternate LEDs (`1010` <-> `0101`) |
| **7** | `7` | 4-bit Binary Counter (0–15) |
| **8** | `8` | All LEDs Blink |
| **9** | `9` | All LEDs OFF |
| **0** | `0` | Reset System |

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Connections
- **Port 0 (`P0.0` - `P0.7`)**: Connected to the 7-segment display segment lines `a` through `g` and `dp` via a 10 kΩ pull-up resistor pack (Port 0 requires external pull-ups due to open-drain configuration).
- **Port 1 (`P1.1` - `P1.4`)**: Connected to 4 output indicator LEDs with 330 Ω current-limiting resistors.
- **Port 2 (`P2.0` - `P2.7`)**: Connected to 4x4 Matrix Keypad:
  - Columns `C1-C4`: `P2.0`, `P2.1`, `P2.2`, `P2.3`
  - Rows `R1-R4`: `P2.4`, `P2.5`, `P2.6`, `P2.7`

---

## 3. Core Logic & Segment Encoding

### Common Anode 7-Segment Lookup Table
| Digit | Hex Value | Binary (`g f e d c b a`) |
|---|---|---|
| 0 | `0x3F` | `0011 1111` |
| 1 | `0x06` | `0000 0110` |
| 2 | `0x5B` | `0101 1011` |
| 3 | `0x4F` | `0100 1111` |
| 4 | `0x66` | `0110 0110` |
| 5 | `0x6D` | `0110 1101` |
| 6 | `0x7D` | `0111 1101` |
| 7 | `0x07` | `0000 0111` |
| 8 | `0x7F` | `0111 1111` |
| 9 | `0x6F` | `0110 1111` |

### Matrix Keypad Scanning Procedure
1. Set all column pins HIGH (`1`) and pull one column LOW (`0`) sequentially.
2. Read the row pins `R1-R4`. If any row pin reads `0`, a key press at the intersection is detected.
3. Call debounce delay. If still `0`, map the row/column coordinate to the designated key value.
4. Output the corresponding 7-segment character on `P0` and execute the designated LED pattern on `P1`.

---

## 4. Inference & Observations

1. **Port 0 Bus Driving**: Port 0 lacks internal pull-up resistors in the AT89S52. Connecting a 10 kΩ external resistor network is necessary to drive the 7-segment display logic levels.
2. **Matrix Scanning Efficiency**: A 4x4 matrix enables 16 unique input keys using only 8 microcontroller pins, minimizing I/O footprint while providing full alphanumeric capability.
3. **Multi-Subsystem Coordination**: The experiment validated seamless synchronization between high-speed matrix keyboard scanning, display multiplexing, and pattern actuation.
