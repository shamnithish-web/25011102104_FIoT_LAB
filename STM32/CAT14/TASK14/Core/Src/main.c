
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : BME280 + ESP8266 + MQTT
  *                   STM32 NUCLEO-F401RE
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"

/* USER CODE BEGIN Includes */
#include "bme280.h"
#include "ESPLib.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */


/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;


/* USER CODE BEGIN PV */

struct bme280_dev bme;
struct bme280_data comp_data;
struct bme280_settings settings;

int8_t rslt;
uint16_t bme280_i2c_addr;

char mqttPayload[150];

/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
void Error_Handler(void);


/* USER CODE BEGIN PFP */

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr);

void user_delay_us(uint32_t period, void *intf_ptr);

void DWT_Delay_Init(void);

/* USER CODE END PFP */


/* USER CODE BEGIN 0 */


/* Initialize DWT for microsecond delay */

void DWT_Delay_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    DWT->CYCCNT = 0;

    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}


/* BME280 I2C Read Function */

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr)
{
    uint16_t address = *(uint16_t *)intf_ptr;

    if (HAL_I2C_Mem_Read(&hi2c1,
                         address,
                         reg_addr,
                         I2C_MEMADD_SIZE_8BIT,
                         reg_data,
                         len,
                         1000) == HAL_OK)
    {
        return 0;
    }

    return -1;
}


/* BME280 I2C Write Function */

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr)
{
    uint16_t address = *(uint16_t *)intf_ptr;

    if (HAL_I2C_Mem_Write(&hi2c1,
                          address,
                          reg_addr,
                          I2C_MEMADD_SIZE_8BIT,
                          (uint8_t *)reg_data,
                          len,
                          1000) == HAL_OK)
    {
        return 0;
    }

    return -1;
}


/* BME280 Microsecond Delay Function */

void user_delay_us(uint32_t period, void *intf_ptr)
{
    uint32_t start = DWT->CYCCNT;

    uint32_t cycles = (SystemCoreClock / 1000000U) * period;

    while ((DWT->CYCCNT - start) < cycles)
    {
        /* Wait */
    }
}


/* USER CODE END 0 */


/**
  * @brief  Main application entry point
  */

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();


    /* USER CODE BEGIN 2 */


    /* 1. Initialize DWT */

    DWT_Delay_Init();


    /* 2. Detect BME280 I2C Address */

    if (HAL_I2C_IsDeviceReady(&hi2c1,
                              0x76 << 1,
                              3,
                              100) == HAL_OK)
    {
        bme280_i2c_addr = 0x76 << 1;
    }

    else if (HAL_I2C_IsDeviceReady(&hi2c1,
                                   0x77 << 1,
                                   3,
                                   100) == HAL_OK)
    {
        bme280_i2c_addr = 0x77 << 1;
    }

    else
    {
        Error_Handler();
    }


    /* 3. Configure Bosch BME280 Driver */

    bme.intf = BME280_I2C_INTF;

    bme.intf_ptr = &bme280_i2c_addr;

    bme.read = user_i2c_read;

    bme.write = user_i2c_write;

    bme.delay_us = user_delay_us;


    /* 4. Initialize BME280 */

    rslt = bme280_init(&bme);

    if (rslt != BME280_OK)
    {
        Error_Handler();
    }


    /* 5. Configure Sensor Settings */

    settings.osr_h = BME280_OVERSAMPLING_1X;

    settings.osr_p = BME280_OVERSAMPLING_1X;

    settings.osr_t = BME280_OVERSAMPLING_1X;

    settings.filter = BME280_FILTER_COEFF_2;

    settings.standby_time = BME280_STANDBY_TIME_1000_MS;


    rslt = bme280_set_sensor_settings(
                BME280_SEL_OSR_PRESS |
                BME280_SEL_OSR_TEMP |
                BME280_SEL_OSR_HUM |
                BME280_SEL_FILTER |
                BME280_SEL_STANDBY,
                &settings,
                &bme
           );

    if (rslt != BME280_OK)
    {
        Error_Handler();
    }


    /* 6. Set Normal Measurement Mode */

    rslt = bme280_set_sensor_mode(BME280_MODE_NORMAL, &bme);

    if (rslt != BME280_OK)
    {
        Error_Handler();
    }


    HAL_Delay(100);


    /* 7. Initialize ESP8266 */

    ESP8266_Init(StationMode, huart1);


    /* 8. Connect to Wi-Fi */

    ESP8266_wifiConnect("SNUC", "snu12345");


    /* 9. Connect to MQTT Broker */

    ESP8266_portConnect("TCP",
                        "broker.emqx.io",
                        "1883");


    /* 10. Configure MQTT */

    MQTT_InitTypeDef_t mqttSetting;

    mqttSetting.keepAlive = 500;

    mqttSetting.connectFlag = CleanSession;

    mqttSetting.clientID = "STM32_BME280";


    MQTT_connectBroker(&mqttSetting);


    HAL_Delay(1000);


    /* USER CODE END 2 */


    /* Infinite Loop */

    while (1)
    {

        /* 11. Read BME280 Sensor Data */

        rslt = bme280_get_sensor_data(
                    BME280_ALL,
                    &comp_data,
                    &bme
               );


        if (rslt == BME280_OK)
        {

            /* 12. Prepare JSON Payload */

            snprintf(mqttPayload,
                     sizeof(mqttPayload),
                     "{\"temperature\":%.2f,"
                     "\"humidity\":%.2f,"
                     "\"pressure\":%.2f}",

                     comp_data.temperature,

                     comp_data.humidity,

                     comp_data.pressure / 100.0
                    );


            /* 13. Publish Data to MQTT */

            MQTT_publishTopic(
                "stm32/bme280/data",
                mqttPayload,
                QoS0
            );

        }

        else
        {
            /* Sensor reading failed */

            strcpy(mqttPayload, "BME280 Read Error");
        }


        /* 14. Wait for 1 Second */

        HAL_Delay(1000);

    }

}


/* System Clock Configuration -----------------------------------------------*/

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(
        PWR_REGULATOR_VOLTAGE_SCALE2
    );


    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;

    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

    RCC_OscInitStruct.PLL.PLLM = 4;

    RCC_OscInitStruct.PLL.PLLN = 84;

    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;

    RCC_OscInitStruct.PLL.PLLQ = 4;


    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }


    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;


    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;

    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;

    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;


    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                            FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}


/* I2C1 Initialization -------------------------------------------------------*/

static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;

    hi2c1.Init.ClockSpeed = 100000;

    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;

    hi2c1.Init.OwnAddress1 = 0;

    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;

    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;

    hi2c1.Init.OwnAddress2 = 0;

    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;

    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
}


/* USART1 Initialization -----------------------------------------------------*/

static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;

    huart1.Init.BaudRate = 115200;

    huart1.Init.WordLength = UART_WORDLENGTH_8B;

    huart1.Init.StopBits = UART_STOPBITS_1;

    huart1.Init.Parity = UART_PARITY_NONE;

    huart1.Init.Mode = UART_MODE_TX_RX;

    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    huart1.Init.OverSampling = UART_OVERSAMPLING_16;


    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}


/* GPIO Initialization -------------------------------------------------------*/

static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    __HAL_RCC_GPIOH_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
}


/* Error Handler -------------------------------------------------------------*/

void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
    }
}


#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add debugging implementation here */
}

#endif
