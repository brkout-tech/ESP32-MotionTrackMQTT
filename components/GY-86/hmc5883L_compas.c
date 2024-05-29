//
// Created by domin on 15.05.2024.
//

#include "hmc5883L_compas.h"
#include "hmc5883L_compas_defs.h"
#include "../ESP32_I2C_custom/ESP32_I2C_custom.h"
#include "esp_log.h"

/**
 * @file hmc5883L_compas.c
 * @brief Implementation file for HMC5883L Compass Sensor functions.
 *
 * This file contains the implementation of functions for initializing and interacting with the HMC5883L compass sensor.
 */

esp_err_t hmc5883l_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    // Device configuration structure
    i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = HMC5883L_I2C_ADDRESS,
            .scl_speed_hz = 100000,  // 100 kHz I2C clock
    };

    // Add device to the bus
    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (ret != ESP_OK) {
        ESP_LOGE("HMC5883L", "Failed to add device: %s", esp_err_to_name(ret));
        return ret;
    }

    // Check identification registers to ensure correct device
    uint8_t idA, idB, idC;
    ret = i2c_read(*dev_handle, HMC5883L_ID_A, &idA, 1);
    ret |= i2c_read(*dev_handle, HMC5883L_ID_B, &idB, 1);
    ret |= i2c_read(*dev_handle, HMC5883L_ID_C, &idC, 1);

    if (ret != ESP_OK || idA != 'H' || idB != '4' || idC != '3') {
        ESP_LOGE("HMC5883L", "Failed to verify device ID: %s", esp_err_to_name(ret));
        return ESP_FAIL;  // Device IDs did not match expected values
    }

    // Configure device for continuous measurement mode
    ret = i2c_write(*dev_handle, HMC5883L_CONFIG_A, HMC5883L_AVERAGING_8 | HMC5883L_DATA_RATE_15_HZ | HMC5883L_NORMAL_MEASUREMENT_CONFIGURATION);
    if (ret != ESP_OK) {
        ESP_LOGE("HMC5883L", "Failed to configure Register A: %s", esp_err_to_name(ret));
        return ret;
    }
    ret |= i2c_write(*dev_handle, HMC5883L_CONFIG_B, HMC5883L_GAIN_1090);
    if (ret != ESP_OK) {
        ESP_LOGE("HMC5883L", "Failed to configure Register B: %s", esp_err_to_name(ret));
        return ret;
    }
    ret |= i2c_write(*dev_handle, HMC5883L_MODE_REGISTER, HMC5883L_CONTINUOUS_MEASUREMENT_MODE);
    if (ret != ESP_OK) {
        ESP_LOGE("HMC5883L", "Failed to configure Mode Register: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}

void hmc5883l_read_data(i2c_master_dev_handle_t dev_handle, hmc5883l_raw_data_t *data_struct) {
    uint8_t data[6];  ///< Buffer for 6 bytes of data
    if (i2c_read(dev_handle, HMC5883L_DATA_X_MSB, data, 6) == ESP_OK) {
        data_struct->x = (int16_t)((data[0] << 8) | data[1]);
        data_struct->y = (int16_t)((data[4] << 8) | data[5]);
        data_struct->z = (int16_t)((data[2] << 8) | data[3]);
    } else {
        ESP_LOGE("HMC5883L", "Failed to read sensor data");
    }
}
