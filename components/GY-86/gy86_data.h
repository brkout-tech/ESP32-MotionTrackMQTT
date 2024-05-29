//
// Created by domin on 20.05.2024.
//

#ifndef ESP_GYRO_GY86_DATA_H
#define ESP_GYRO_GY86_DATA_H

#include "stdlib.h"
#include "stdbool.h"
#include "mpu6050_gyro_accel_defs.h"
#include "ms5611_baro_defs.h"
#include "hmc5883L_compas_defs.h"
#include "../ESP32_Mqtt_custom/ESP32_Mqtt_custom_defs.h"
#include "../ESP32_I2C_custom/ESP32_I2C_custom.h"
#include "gy86_data_defs.h"

/**
 * @file gy86_data.h
 * @brief Header file for GY-86 Sensor Suite functions.
 *
 * This file contains the function prototypes for initializing and interacting with the GY-86 sensor suite,
 * which includes functions for reading data from the sensors, calculating altitude, orientation, and heading.
 */


/**
 * @brief Initialize the GY-86 sensor suite.
 * @param bus_handle I2C master bus handle.
 */
void init_gy86_module(i2c_master_bus_handle_t bus_handle);

/**
 * @brief Get sensor data from the GY-86 sensor suite.
 * @param count Pointer to store the number of sensors.
 * @return Pointer to the array of sensor data.
 */
sensor_data_t* get_sensor_data(int *count);

/**
 * @brief Calculate the altitude based on the pressure.
 * @param pressure_mbar Pressure in millibars.
 * @return Altitude in meters.
 */
float calculate_altitude(float pressure_mbar);

/**
 * @brief Calculate the orientation (pitch and roll) based on the accelerometer data.
 * @param data Pointer to the raw accelerometer data.
 * @return Calculated orientation.
 */
sensor_orientation_t calculate_orientation(const mpu6050_raw_data_t *data);

/**
 * @brief Calculate the heading (compass direction) based on the magnetometer and accelerometer data.
 * @param mag_data Pointer to the raw magnetometer data.
 * @param accel_data Pointer to the raw accelerometer data.
 * @return Calculated heading in degrees.
 */
float calculate_heading(const hmc5883l_raw_data_t *mag_data, const mpu6050_raw_data_t *accel_data);

/**
 * @brief Get the compass direction based on the heading.
 * @param heading Heading in degrees.
 * @return Compass direction as a string.
 */
const char* get_compass_direction(float heading);

#endif //ESP_GYRO_GY86_DATA_H
