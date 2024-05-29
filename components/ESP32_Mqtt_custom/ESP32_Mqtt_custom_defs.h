//
// Created by domin on 24.05.2024.
//

#ifndef ESP_GYRO_ESP32_MQTT_CUSTOM_DEFS_H
#define ESP_GYRO_ESP32_MQTT_CUSTOM_DEFS_H

/**
 * @file ESP32_Mqtt_custom_defs.h
 * @brief Definitions for custom MQTT sensor data and configurations.
 *
 * This file contains the type definitions for sensor values, sensor data, and sensor configurations
 * used in the custom MQTT implementation on the ESP32 platform.
 */

/**
 * @enum value_type_t
 * @brief Enum representing the type of a sensor value.
 */
typedef enum {
    VALUE_TYPE_FLOAT,   ///< Floating point value
    VALUE_TYPE_INT,     ///< Integer value
    VALUE_TYPE_DOUBLE,  ///< Double precision floating point value
    VALUE_TYPE_STRING   ///< String value
} value_type_t;

/**
 * @struct sensor_value_t
 * @brief Struct representing a sensor value with its type and actual value.
 */
typedef struct {
    value_type_t type; ///< Type of the sensor value
    union {
        float float_value;       ///< Floating point value
        int int_value;           ///< Integer value
        double double_value;     ///< Double precision floating point value
        const char* string_value; ///< String value
    };
} sensor_value_t;

/**
 * @struct sensor_data_t
 * @brief Struct representing the data of a sensor, including the topic, value, and type.
 */
typedef struct {
    const char *topic;        ///< MQTT topic for the sensor data
    sensor_value_t value;     ///< Value of the sensor
    const char *sensor_type;  ///< Type of the sensor
} sensor_data_t;

/**
 * @struct sensor_config_t
 * @brief Struct representing the configuration of a sensor for MQTT discovery messages.
 */
typedef struct {
    const char *sensor_type;          ///< Type of the sensor
    const char *device_class;         ///< Device class of the sensor
    const char *state_topic;          ///< MQTT topic for the sensor state
    const char *unit_of_measurement;  ///< Unit of measurement for the sensor
    const char *value_template;       ///< Value template for the sensor
    const char *unique_id;            ///< Unique ID for the sensor
    const char *identifiers;          ///< Identifiers for the device
    const char *name;                 ///< Name of the device
    const char *manufacturer;         ///< Manufacturer of the device
    const char *model;                ///< Model of the device
} sensor_config_t;

#endif //ESP_GYRO_ESP32_MQTT_CUSTOM_DEFS_H
