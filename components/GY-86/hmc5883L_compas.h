//
// Created by domin on 15.05.2024.
//

#ifndef ESP_GYRO_HMC5883L_COMPAS_H
#define ESP_GYRO_HMC5883L_COMPAS_H

#include "driver/i2c_master.h"
#include "hmc5883L_compas_defs.h"

/**
 * @file hmc5883L_compas.h
 * @brief Header file for HMC5883L Compass Sensor functions.
 *
 * This file contains the function prototypes for initializing and interacting with the HMC5883L compass sensor.
 */

/**
 * @brief Initialize the HMC5883L magnetometer sensor.
 * @param bus_handle I2C master bus handle.
 * @param dev_handle Pointer to the I2C device handle.
 * @return esp_err_t ESP_OK on success, or an error code on failure.
 */
esp_err_t hmc5883l_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Read magnetometer data from the HMC5883L sensor.
 * @param dev_handle I2C device handle.
 * @param data_struct Pointer to the structure to hold the raw magnetometer data.
 */
void hmc5883l_read_data(i2c_master_dev_handle_t dev_handle, hmc5883l_raw_data_t *data_struct);

#endif //ESP_GYRO_HMC5883L_COMPAS_H
