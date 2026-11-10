# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-12 |
| **DATE** | 23/10/2026 (Week 12) |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I2C and Bosch Sensor API + HTTP Node Analytics |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE + BME280 Sensor + ESP8266 Wi-Fi + Node-RED Dashboard |
| **TASK NO** | I2C Bosch Sensor Driver, JSON Response Serialization, and Statistical Analytics |

---

## 1. Problem Statement

Develop an STM32-based environmental sensing application to interface a Bosch BME280 sensor over $I^2C$ and obtain factory-calibrated, compensated temperature, pressure, and humidity measurements using the official Bosch Sensortec Sensor API. Construct dynamic JSON HTTP payloads and deliver telemetry to a Node-RED analytics flow for statistical evaluation (minimum, maximum, average).

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Connections
- **$I^2C1$ Bus**:
  - `PB8` -> BME280 **SCL** (Serial Clock, 100 kHz standard mode)
  - `PB9` -> BME280 **SDA** (Serial Data)
  - 4.7 kΩ pull-up resistors to 3.3V on both bus lines.
  - SDO pin tied to GND: 7-bit $I^2C$ device address = `0x76` (`BME280_I2C_ADDR_PRIM`).
- **Power**: 3.3V and GND from Nucleo power headers.
- **Wi-Fi Bridge**: ESP8266 connected on `USART2` (`PA2`/`PA3`) communicating with Node-RED over Wi-Fi.

---

## 3. Core Logic & Bosch API Implementation

### Low-Level $I^2C$ Hardware Abstraction Functions
```c
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *(uint8_t*)intf_ptr;
    if (HAL_I2C_Mem_Read(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, len, 1000) == HAL_OK)
        return BME280_OK;
    return BME280_E_COMM_FAIL;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *(uint8_t*)intf_ptr;
    if (HAL_I2C_Mem_Write(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)reg_data, len, 1000) == HAL_OK)
        return BME280_OK;
    return BME280_E_COMM_FAIL;
}

void user_delay_us(uint32_t period, void *intf_ptr) {
    HAL_Delay((period / 1000) + 1);
}
```

### Dynamic JSON Payload Formatting
```c
char json[200];
snprintf(json, sizeof(json),
    "{\"status\":\"success\",\"temperature\":%.2f,\"humidity\":%.2f,\"pressure\":%.2f}",
    comp_data.temperature, comp_data.humidity, comp_data.pressure);

int content_length = strlen(json);
snprintf(http_response, sizeof(http_response),
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s", content_length, json);
```

### Node-RED Statistical Analytics Table
| Parameter | Minimum | Maximum | Average |
|---|---|---|---|
| **Temperature (°C)** | 27.91 | 29.02 | 28.46 |
| **Humidity (%RH)** | 59.80 | 64.20 | 62.15 |
| **Pressure (hPa)** | 1007.84 | 1009.31 | 1008.56 |

---

## 4. Inference & Observations

1. **Factory Trimming Register Compensation**: The raw ADC values read from registers `0xF7` - `0xFE` require 24 calibration parameters stored in sensor NVM. The Bosch driver computes true physical values via 64-bit fixed/floating point formulas.
2. **Chip ID Verification**: Querying register `0xD0` returned `0x60`, proving successful $I^2C$ physical layer communication before sensor configuration.
3. **JSON REST Integration**: Serving standards-compliant JSON over HTTP enabled zero-friction ingestion into Node-RED dashboards for real-time charting and statistical aggregation.
