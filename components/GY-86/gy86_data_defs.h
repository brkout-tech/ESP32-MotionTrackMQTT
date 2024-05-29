//
// Created by domin on 24.05.2024.
//

#ifndef ESP_GYRO_GY86_DATA_DEFS_H
#define ESP_GYRO_GY86_DATA_DEFS_H

#include "../ESP32_Mqtt_custom/ESP32_Mqtt_custom_defs.h"

#define SEA_LEVEL_PRESSURE_HPA (1013.25)
#define PI 3.14159265358979323846
#define RAD_TO_DEG 57.2957795131

/**
 * @file gy86_data_defs.h
 * @brief Definitions for GY-86 Sensor Suite.
 *
 * This file contains the sensor configurations and data arrays used
 * for the GY-86 sensor suite, which includes temperature, pressure, roll,
 * pitch, altitude, direction, compass, and acceleration sensors.
 */

/**
 * @brief Array of sensor configurations for the GY-86 sensor suite.
 */
static const sensor_config_t sensor_configs[] = {
        {
                "temperature",
                "temperature",
                "homeassistant/sensor/GY86/temperature/state",
                "°C",
                "{{ value_json.temperature }}",
                "GY86_temperature",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "pressure",
                "pressure",
                "homeassistant/sensor/GY86/pressure/state",
                "hPa",
                "{{ value_json.pressure }}",
                "GY86_pressure",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "roll",
                "None",
                "homeassistant/sensor/GY86/roll/state",
                "degrees",
                "{{ value_json.roll }}",
                "GY86_roll",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "pitch",
                "None",
                "homeassistant/sensor/GY86/pitch/state",
                "degrees",
                "{{ value_json.pitch }}",
                "GY86_pitch",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "altitude",
                "distance",
                "homeassistant/sensor/GY86/altitude/state",
                "m",
                "{{ value_json.altitude }}",
                "GY86_altitude",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "direction",
                "None",
                "homeassistant/sensor/GY86/direction/state",
                "degrees",
                "{{ value_json.direction }}",
                "GY86_direction",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "compass",
                "None",
                "homeassistant/sensor/GY86/compass/state",
                "",
                "{{ value_json.compass }}",
                "GY86_compass",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "acceleration",
                "speed",
                "homeassistant/sensor/GY86/acceleration/X/state",
                "G",
                "{{ value_json.acceleration_x }}",
                "GY86_acceleration_x",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "acceleration",
                "speed",
                "homeassistant/sensor/GY86/acceleration/Y/state",
                "G",
                "{{ value_json.acceleration_y }}",
                "GY86_acceleration_y",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        },
        {
                "acceleration",
                "speed",
                "homeassistant/sensor/GY86/acceleration/Z/state",
                "G",
                "{{ value_json.acceleration_z }}",
                "GY86_acceleration_z",
                "GY86",
                "GY86 Sensor Suite",
                "Generic",
                "GY86 Multi-Sensor"
        }
};

/**
 * @brief Array of sensor data for the GY-86 sensor suite.
 */
static sensor_data_t sensor_data_array[] = {
        {sensor_configs[0].state_topic, {VALUE_TYPE_FLOAT, {.float_value = 0.0}}, "temperature"},
        {sensor_configs[1].state_topic, {VALUE_TYPE_FLOAT, {.float_value = 0.0}}, "pressure"},
        {sensor_configs[2].state_topic, {VALUE_TYPE_FLOAT, {.float_value = 0.0}}, "roll"},
        {sensor_configs[3].state_topic, {VALUE_TYPE_FLOAT, {.float_value = 0.0}}, "pitch"},
        {sensor_configs[4].state_topic, {VALUE_TYPE_FLOAT, {.float_value = 0.0}}, "altitude"},
        {sensor_configs[5].state_topic, {VALUE_TYPE_FLOAT, {.float_value = 0.0}}, "direction"},
        {sensor_configs[6].state_topic, {VALUE_TYPE_STRING, {.string_value = "X"}}, "compass"},
        {sensor_configs[7].state_topic, {VALUE_TYPE_INT, {.int_value = 0}}, "acceleration_x"},
        {sensor_configs[8].state_topic, {VALUE_TYPE_INT, {.int_value = 0}}, "acceleration_y"},
        {sensor_configs[9].state_topic, {VALUE_TYPE_INT, {.int_value = 0}}, "acceleration_z"}
};

/**
 * @brief Number of sensors in the GY-86 sensor suite.
 */
#define NUM_SENSORS (sizeof(sensor_configs) / sizeof(sensor_configs[0]))

/**
 * @brief Structure to hold the sensor orientation data (pitch and roll).
 */
typedef struct {
    float pitch;  ///< Pitch angle in degrees
    float roll;   ///< Roll angle in degrees
} sensor_orientation_t;

#endif //ESP_GYRO_GY86_DATA_DEFS_H
