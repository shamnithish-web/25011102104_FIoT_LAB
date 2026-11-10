# EXPERIMENT DETAILS

| Field | Details |
|---|---|
| **EXP** | CONTINUOUS LAB EVALUATION-13 |
| **DATE** | 27/10/2026 (Week 13) |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I2C and (MQTT) using Custom Built ESP8266 API - Node Analytics |
| **HARDWARE SETUP / PLATFORM** | STM32 NUCLEO-F401RE + BME280 + ESP8266 Wi-Fi + EMQX MQTT Cloud Broker + Node-RED |
| **TASK NO** | MQTT Telemetry Publishing, Subscription Handlers, and Cloud Node Analytics |

---

## 1. Problem Statement

As a continuation of the environmental sensing pipeline, implement an end-to-end MQTT telemetry system using the custom `ESPLib` driver library on the STM32F401RE:
1. Connect the ESP8266 Wi-Fi module to the local access point.
2. Establish a TCP socket connection to the public MQTT broker (`broker.emqx.io:1883`).
3. Connect the MQTT client session with a unique client ID.
4. Publish periodic BME280 environmental telemetry to the topic `stm32/test/data` at QoS 0.
5. Subscribe to incoming control commands on topic `IOT` and process received payloads via non-blocking SysTick timer handlers.
6. Build a Node-RED dashboard for live gauge display and actuation.

---

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

### Hardware Connections
- **BME280 Sensor**: Connected to $I^2C1$ (`PB8` SCL, `PB9` SDA) at address `0x76`.
- **Wemos D1 Mini (ESP8266)**: Connected to `USART1` / `USART2`:
  - `USART_TX` -> ESP8266 `RX`
  - `USART_RX` <- ESP8266 `TX`
  - Power: 3.3V, Common GND.
- **MQTT Cloud Broker**: `broker.emqx.io`, Port 1883 (TCP Unencrypted).

---

## 3. Core Logic & Source Code

### MQTT Client Initialization (`CAT13/Core/Src/main.c`)
```c
#include "ESPLib.h"
#include "bme280.h"

char mqttData[100];
char mqttTopic[32];

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    // 1. Initialize ESP8266 in Station Mode on USART1
    ESP8266_Init(StationMode, huart1);
    
    // 2. Connect to Wi-Fi Access Point
    ESP8266_wifiConnect("OnePlus", "12345678910");
    
    // 3. Connect TCP socket to public MQTT Broker
    ESP8266_portConnect("TCP", "broker.emqx.io", "1883");
    
    // 4. Configure MQTT Session Settings
    MQTT_InitTypeDef_t mqttSetting;
    mqttSetting.keepAlive = 500;
    mqttSetting.connectFlag = CleanSession;
    mqttSetting.clientID = "STM32_25011102104";
    MQTT_connectBroker(&mqttSetting);
    
    // 5. Subscribe to Remote Command Topic
    MQTT_subscribeTopic("IOT", 0);

    while (1) {
        // Read BME280 Environmental Data
        bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
        
        // Format Telemetry Payload
        snprintf(mqttData, sizeof(mqttData), "T:%.1f C, H:%.1f%%, P:%.1f hPa",
                 comp_data.temperature, comp_data.humidity, comp_data.pressure);
                 
        // Publish to MQTT Topic
        MQTT_publishTopic("stm32/test/data", mqttData, QoS0);
        
        // Handle incoming subscribed messages
        MQTTDataHandler(mqttTopic, mqttData);
        
        HAL_Delay(1000);
    }
}

// Non-blocking Keep-Alive Timer in SysTick IRQ Handler
void SysTick_Handler(void) {
    HAL_IncTick();
    MQTTTimer(); // Maintains keep-alive ping packets
}
```

---

## 4. Inference & Observations

1. **Lightweight Pub/Sub Efficiency**: Compared to HTTP request-response polling, MQTT publish-subscribe minimizes network overhead and latency, making it the industry standard for battery-constrained IoT devices.
2. **Keep-Alive Heartbeats**: The `SysTick_Handler` non-blocking timer routine (`MQTTTimer()`) ensures periodic PINGREQ packets are dispatched to prevent the broker from dropping the client socket.
3. **Full Cloud Integration**: Telemetry published by the STM32 was received and visualized on Node-RED dashboard gauges, successfully proving the complete edge-to-cloud IoT architecture.
