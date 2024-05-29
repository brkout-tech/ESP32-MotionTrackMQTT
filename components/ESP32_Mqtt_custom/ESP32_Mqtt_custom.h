//
// Created by domin on 26.04.2024.
//

#ifndef ESP_TEST_MANUELL_CUSTOM_MQTT_H
#define ESP_TEST_MANUELL_CUSTOM_MQTT_H

#include "mqtt_client.h"
#include "ESP32_Mqtt_custom_defs.h"
#include "string.h"

/**
 * @file ESP32_Mqtt_custom.h
 * @brief Header file for custom MQTT functions on the ESP32.
 *
 * This file contains the default configurations, variable declarations, and function prototypes
 * for custom MQTT operations on the ESP32 platform.
 */

#define MQTT_BROKER     "mqtt://homeassistant.local:1883"     ///< Default MQTT broker URI
#define MQTT_USERNAME   "Dominik"                             ///< Default MQTT username
#define MQTT_PASSWORD   "dv7-2160eg"                          ///< Default MQTT password
#define MQTT_TAG        "MQTT"

// Variables for MQTT Configuration
extern const char* mqtt_broker;
extern const char* mqtt_username;
extern const char* mqtt_password;
extern const char* mqtt_log_tag;                        ///< Tag for ESP logging

// Setter, Getter for Configuration

/**
 * @brief Set the MQTT broker URI.
 * @param broker URI of the MQTT broker.
 */
void set_mqtt_broker(const char* broker);

/**
 * @brief Set the MQTT username.
 * @param username MQTT username.
 */
void set_mqtt_username(const char* username);

/**
 * @brief Set the MQTT password.
 * @param password MQTT password.
 */
void set_mqtt_password(const char* password);

/**
 * @brief Set the log tag for MQTT operations.
 * @param log_tag Log tag string.
 */
void set_mqtt_log_tag(const char* log_tag);

/**
 * @brief Get the MQTT broker URI.
 * @return URI of the MQTT broker.
 */
const char* get_mqtt_broker();

/**
 * @brief Get the MQTT username.
 * @return MQTT username.
 */
const char* get_mqtt_username();

/**
 * @brief Get the MQTT password.
 * @return MQTT password.
 */
const char* get_mqtt_password();

/**
 * @brief Get the log tag for MQTT operations.
 * @return Log tag string.
 */
const char* get_mqtt_log_tag();

/**
 * @brief Event handler for MQTT events.
 * @param handler_args Handler arguments.
 * @param base Event base.
 * @param event_id Event ID.
 * @param event_data Event data.
 */
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

/**
 * @brief Initialize and start the MQTT client.
 * @return Handle to the MQTT client.
 */
esp_mqtt_client_handle_t mqtt_app_start(void);

/**
 * @brief Send discovery messages for all sensors.
 * @param client MQTT client handle.
 * @param sensor_configs Array of sensor configurations.
 * @param number_of_configs Number of sensor configurations.
 */
void send_all_sensor_discoveries(esp_mqtt_client_handle_t client, const sensor_config_t *sensor_configs, int number_of_configs);

/**
 * @brief Send sensor data.
 * @param client MQTT client handle.
 * @param sensor_data_array Array of sensor data.
 * @param data_count Number of sensor data entries.
 */
void send_sensor_data_array(esp_mqtt_client_handle_t client, const sensor_data_t *sensor_data_array, size_t data_count);

#endif //ESP_TEST_MANUELL_CUSTOM_MQTT_H
