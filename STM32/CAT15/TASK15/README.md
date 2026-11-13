# TASK15: Course Project — College Sensor vs Chennai Weather Intelligence & Recommendations

## Experiment Metadata

| Field | Description |
|---|---|
| **EXP** | CAT15 |
| **DATE** | 05/11/2026 |
| **NAME OF EXP** | Course Project: College Sensor vs Chennai Weather Intelligence & Recommendations |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE (ARM Cortex-M4), BME280 Sensor (I2C), ESP8266 Wi-Fi Modem (UART), EMQX Public MQTT Broker (broker.emqx.io:1883), OpenWeather API, Node-RED Dashboard |
| **TASK NO** | TASK15 |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections & Hardware Interface

| Nucleo Pin | Target Device | Interface / Pin | Function |
|---|---|---|---|
| PB8 | BME280 Sensor Module | SCL | I2C1 Bus Clock (100 kHz Standard Mode) |
| PB9 | BME280 Sensor Module | SDA | I2C1 Bus Data Line |
| PA9 | ESP8266 Wi-Fi Module | RXD (Pin D4) | Modem Transmit Line (USART1_TX @ 115200 bps) |
| PA10 | ESP8266 Wi-Fi Module | TXD (Pin D3) | Modem Receive Line (USART1_RX @ 115200 bps) |
| PA5 | On-board User LED LD2 | Anode | Telemetry Strobe & System Heartbeat Indicator |
| 3.3V, GND | Power Bus | VCC, GND | Regulated 3.3V System Power Supply |
| Internet / Wi-Fi | EMQX Public Broker | broker.emqx.io:1883 | Edge-to-Cloud MQTT Uplink (QoS 0) |
| Cloud API | OpenWeatherMap | REST Endpoint | Regional Reference Meteorological Data (Chennai) |
| Localhost / LAN | Node-RED Server | Port 1880 / :1880/ui | Stream Processing, Rules Engine & UI Dashboard |

---

## Node-RED Environmental Intelligence Dashboard

![Node-RED Dashboard Telemetry](dashboard.png)

### Real-Time Environmental Comparison Table (College vs Chennai City)

| Environmental Parameter | College Ground (BME280 Sensor) | Chennai City (OpenWeather API) | Difference ($\Delta$ Variance) | Environmental Impact |
|---|:---:|:---:|:---:|---|
| **Temperature** | 28.67 °C | 26.98 °C | +1.69 °C (warmer) | Thermal comfort & ambient heat load |
| **Relative Humidity** | 71.25 % | 81.00 % | -9.75 % (drier) | Air moisture saturation & sweat evaporation |
| **Barometric Pressure** | 1009.97 hPa | 1014.00 hPa | -4.03 hPa (Sea Level Baseline) | Atmospheric pressure & weather stability |
| **Heat Index ("Feels-Like")** | 32.20 °C | 29.80 °C | +2.40 °C | Physiological thermal strain based on humidity |
| **Dew Point Temperature** | 22.90 °C | 23.40 °C | Moist Air | Moisture condensation & air mugginess threshold |

### Sensor-Based Recommendations (With Defined Variable Ranges)

1. **Temperature (`28.67 °C` - [WARM / MILD HEAT], Active Range: `26.1 °C - 32.0 °C`):**  
   *Action Recommendation:* Warm ambient conditions detected. Operate ceiling fans to promote convective cooling, draw window blinds to block solar radiation, and maintain steady hydration.
2. **Relative Humidity (`71.25 %` - [HUMID / MUGGY], Active Range: `60.1 % - 75.0 %`):**  
   *Action Recommendation:* Elevated moisture detected. Perspiration dries slowly causing mugginess. Increase airflow via exhaust or ceiling fans to improve body cooling.
3. **Barometric Pressure (`1009.97 hPa` - [STABLE / NORMAL PRESSURE], Active Range: `1005.0 - 1015.0 hPa`):**  
   *Action Recommendation:* Normal coastal sea level barometric pressure. Indicates steady, predictable weather conditions with stable atmospheric stability.
4. **Heat Index ("Feels-Like") (`32.2 °C` - [EXTREME CAUTION], Active Range: `32.1 °C - 41.0 °C`):**  
   *Action Recommendation:* Sunstroke, muscle cramps, and heat exhaustion possible with prolonged exposure. Limit outdoor sun exposure and rest in air-cooled area.
5. **Dew Point (`22.9 °C` - [HUMID & STUFFY], Active Range: `21.1 °C - 24.0 °C`):**  
   *Action Recommendation:* Noticeable latent moisture. Air feels heavy; run ceiling or exhaust fans to avoid evaporative cooling issues.

### 6 Comparative Environmental Insights (College Campus vs Chennai City)

1. **Microclimate Temperature Differential:** College location is 1.7 °C warmer than central Chennai (28.67 °C vs 26.98 °C). Campus greenery and open layout provide noticeable thermal moderation compared to the city's concrete urban heat island.
2. **Relative Humidity & Moisture Comparison:** College air is 9.8 % drier than coastal Chennai (71.25 % vs 81 %). Drier air accelerates natural sweat evaporation, keeping the environment crisp.
3. **Heat Index (Feels-Like) Physiological Load:** Local perceived heat index is 32.2 °C compared to Chennai city's 29.8 °C (Variance: +2.4 °C). Accounting for air moisture, this reflects actual physiological thermal strain on the human body.
4. **Dew Point & Atmospheric Latent Moisture:** College dew point is 22.9 °C (Chennai city: 23.4 °C). Dew point indicates the temperature at which air saturates with water vapor; values below 21 °C signify pleasant, non-clammy conditions.
5. **Barometric Pressure & Weather Stability:** Atmospheric pressure is 1009.97 hPa. Pressure levels are steady and consistent with regional coastal baselines, indicating settled atmospheric conditions with zero immediate precipitation danger.
6. **Overall Environmental Comfort Assessment:** Current college environmental state (28.67 °C, 71.25% RH) offers a stable environment compared to central Chennai (26.98 °C, 81% RH).

---

## Node-RED Telemetry Flow Architecture

![Node-RED Flow Architecture](nodered_flow.png)

---

## MQTT Telemetry Architecture & JSON Payload

The STM32 edge sensor node formats calibrated environmental metrics into structured JSON and publishes periodically to the EMQX public broker:

- **Broker Address:** `broker.emqx.io:1883`
- **Active MQTT Topic:** `college/weather/bme280`
- **Quality of Service (QoS):** `QoS 0`
- **Payload Schema:**
```json
{
  "temp": 28.67,
  "humidity": 71.25,
  "pressure": 1009.97,
  "node": "STM32_BME280_COLLEGE"
}
```

---

## Core Logic & Pseudocode

```text
1. Initialize STM32 HAL, System Clock (84 MHz), I2C1 (100 kHz), and USART1 (115200 baud).
2. Initialize BME280 sensor structure with hardware I2C read/write/delay callback wrappers.
3. Verify BME280 Chip ID (0x60) and load factory trimming coefficients.
4. Configure sensor oversampling settings and enter Normal Mode.
5. Initialize ESP8266 modem:
   a. Send 'AT' ping and await 'OK'.
   b. Set station mode: 'AT+CWMODE=1'.
   c. Associate with Wi-Fi AP: 'AT+CWJAP="SSID","PASSWORD"'.
6. Open TCP connection to MQTT broker:
   'AT+CIPSTART="TCP","broker.emqx.io",1883'
7. Formulate and transmit MQTT CONNECT control packet (Client ID: "STM32_BME280").
8. In superloop (every 3 seconds):
   a. Sample BME280: bme280_get_sensor_data(BME280_ALL, &comp_data, &bme).
   b. Format JSON payload with calibrated temperature, humidity, and barometric pressure.
   c. Transmit MQTT PUBLISH packet to topic 'college/weather/bme280'.
   d. Strobe User LED (PA5) to signal transmission.
9. Node-RED Pipeline:
   a. Ingest MQTT stream from 'college/weather/bme280'.
   b. Ingest Chennai weather via OpenWeather API (triggered every 5 min).
   c. Execute mathematical formulas for Heat Index and Dew Point.
   d. Evaluate 5 variable threshold rules and generate actionable recommendations.
   e. Compute comparative microclimate insights and render live UI dashboard.
```

---

## Source Code Implementation

```c
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : BME280 + ESP8266 + MQTT College Weather Telemetry Node
  *                   STM32 NUCLEO-F401RE Course Project
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "bme280.h"
#include "ESPLib.h"
#include <stdio.h>
#include <string.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

struct bme280_dev bme;
struct bme280_data comp_data;
struct bme280_settings settings;
char mqttPayload[160];

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    /* 1. Initialize BME280 Environmental Sensor */
    bme.intf = BME280_I2C_INTF;
    bme.read = user_i2c_read;
    bme.write = user_i2c_write;
    bme.delay_us = user_delay_us;
    bme280_init(&bme);

    /* 2. Configure Sensor Settings */
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_1X;
    settings.osr_t = BME280_OVERSAMPLING_1X;
    settings.filter = BME280_FILTER_COEFF_OFF;
    bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &bme);
    bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &bme);

    /* 3. Connect to Wi-Fi Access Point */
    ESP_Init(&huart1);
    WIFI_connectAP("iPhone", "rith1100");

    /* 4. Connect to Cloud MQTT Broker */
    MQTT_connectBroker("broker.emqx.io", 1883);
    MQTT_InitTypeDef_t mqttSetting;
    mqttSetting.keepAlive = 500;
    mqttSetting.connectFlag = CleanSession;
    mqttSetting.clientID = "STM32_BME280_COLLEGE";
    MQTT_configure(&mqttSetting);

    /* 5. Continuous Telemetry Transmission Loop */
    while (1) {
        if (bme280_get_sensor_data(BME280_DATA_ALL, &comp_data, &bme) == BME280_OK) {
            snprintf(mqttPayload, sizeof(mqttPayload),
                     "{"temp":%.2f,"humidity":%.2f,"pressure":%.2f,"node":"STM32_BME280_COLLEGE"}",
                     comp_data.temperature,
                     comp_data.humidity,
                     comp_data.pressure / 100.0);

            MQTT_publishTopic("college/weather/bme280", mqttPayload, QoS0);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
        HAL_Delay(3000);
    }
}
```

---

## Inference & Technical Analysis

1. **Microclimate Phenomenon:** The +1.69 °C positive temperature delta accompanied by a -9.75 % negative humidity delta clearly demonstrates microclimatic variance between the college campus and coastal Chennai city.
2. **Heat Index vs Ambient Temperature:** The perceived heat index (32.2 °C) is significantly higher than raw temperature (28.67 °C) due to elevated relative humidity (71.25 %), justifying the automated "Extreme Caution" recommendation.
3. **Architecture Robustness:** Decoupling the STM32 edge sensing node, cloud MQTT message routing, and Node-RED analytics engine creates a resilient, industrial-grade IoT environmental monitoring architecture.
