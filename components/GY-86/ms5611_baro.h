//
// Created by domin on 15.05.2024.
//

#ifndef ESP_GYRO_MS5611_BARO_H
#define ESP_GYRO_MS5611_BARO_H

#include "driver/i2c_master.h"
#include "ms5611_baro_defs.h"

/**
 * @file ms5611_baro.h
 * @brief Header file for MS5611 Barometer Sensor functions.
 *
 * This file contains the function prototypes for initializing and interacting with the MS5611 barometer sensor.
 */

/**
 * @brief Initialize the MS5611 sensor.
 * @param bus_handle I2C master bus handle.
 * @param dev_handle Pointer to the I2C device handle.
 * @return esp_err_t ESP_OK on success, or an error code on failure.
 */
esp_err_t ms5611_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Read pressure and temperature from the MS5611 sensor.
 * @param dev_handle I2C device handle.
 * @param data Pointer to the structure to hold the pressure and temperature data.
 * @return esp_err_t ESP_OK on success, or an error code on failure.
 */
esp_err_t ms5611_read_pressure_and_temperature(i2c_master_dev_handle_t dev_handle, ms5611_data_t *data);

/**
 * @brief Reset the MS5611 sensor.
 * @param dev_handle I2C device handle.
 */
void ms5611_reset(i2c_master_dev_handle_t dev_handle);

#endif //ESP_GYRO_MS5611_BARO_H
