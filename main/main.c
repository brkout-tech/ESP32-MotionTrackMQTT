#include <stdio.h>
#include <nvs_flash.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../components/ESP32_I2C_custom/ESP32_I2C_custom.h"
#include "../components/ESP32_Wifi_custom/ESP32_Wifi_custom.h"
#include "../components/GY-86/gy86_data.h"
#include "../components/ESP32_Mqtt_custom/ESP32_Mqtt_custom.h"

/**
 * @file main.c
 * @brief Main application file for initializing and using the GY-86 sensor suite with MQTT on ESP32.
 *
 * This file contains the main function which initializes the I2C bus, GY-86 sensors, WiFi, and MQTT.
 * It periodically reads sensor data and publishes it to an MQTT broker.
 */

/**
 * @brief Main application entry point.
 *
 * This function initializes the I2C bus, GY-86 sensor suite, NVS, WiFi, and MQTT. It then enters a loop
 * where it periodically reads sensor data from the GY-86 sensors and publishes the data to an MQTT broker.
 */
void app_main() {
    // I2C bus handle
    i2c_master_bus_handle_t bus_handle = NULL;
    i2c_master_init(&bus_handle);

    // Initialize GY-86 sensor suite
    init_gy86_module(bus_handle);

    // Initialize NVS (necessary for WiFi)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize WiFi in station mode
    wifi_init_sta();

    // Initialize and start MQTT client
    esp_mqtt_client_handle_t mqttClientHandle;
    mqttClientHandle = mqtt_app_start();

    // Send sensor discovery messages to MQTT broker
    send_all_sensor_discoveries(mqttClientHandle, sensor_configs, NUM_SENSORS);

    while (1) {
        int sensor_count;
        // Get sensor data from GY-86 sensor suite
        sensor_data_t *sensor_data = get_sensor_data(&sensor_count);
        // Send sensor data to MQTT broker
        send_sensor_data_array(mqttClientHandle, sensor_data, sensor_count);

        // Delay for 20 seconds
        vTaskDelay(pdMS_TO_TICKS(20000));
    }
}
