//
// Created by domin on 15.05.2024.
//

#ifndef ESP_GYRO_MPU6050_GYRO_ACCEL_H
#define ESP_GYRO_MPU6050_GYRO_ACCEL_H

#include "driver/i2c_master.h"
#include "mpu6050_gyro_accel_defs.h"

/**
 * @file mpu6050_gyro_accel.h
 * @brief Header file for MPU6050 Gyroscope and Accelerometer Sensor functions.
 *
 * This file contains the function prototypes for initializing and interacting with the MPU6050 gyroscope and accelerometer sensor.
 */

#define I2C_MASTER_TIMEOUT_MS 1000  ///< Timeout for I2C operations in milliseconds

/**
 * @brief Initialize the MPU6050 sensor.
 * @param bus_handle I2C master bus handle.
 * @param dev_handle Pointer to the I2C device handle.
 * @return esp_err_t ESP_OK on success, or an error code on failure.
 */
esp_err_t mpu6050_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Read accelerometer and gyroscope data from the MPU6050 sensor.
 * @param dev_handle I2C device handle.
 * @param data_struct Pointer to the structure to hold the raw accelerometer and gyroscope data.
 */
void mpu6050_read_data(i2c_master_dev_handle_t dev_handle, mpu6050_raw_data_t *data_struct);

#endif //ESP_GYRO_MPU6050_GYRO_ACCEL_H
