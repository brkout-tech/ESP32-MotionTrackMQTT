//
// Created by domin on 15.05.2024.
//

#include <esp_log.h>
#include "string.h"
#include "mpu6050_gyro_accel.h"
#include "../ESP32_I2C_custom/ESP32_I2C_custom.h"

/**
 * @file mpu6050_gyro_accel.c
 * @brief Implementation file for MPU6050 Gyroscope and Accelerometer Sensor functions.
 *
 * This file contains the implementation of functions for initializing and interacting with the MPU6050 gyroscope and accelerometer sensor.
 */

esp_err_t mpu6050_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = MPU6050_I2C_ADDRESS,
            .scl_speed_hz = 100000,
    };

    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to add MPU6050 device: %s", esp_err_to_name(ret));
        return ret;
    }

    uint8_t whoAmI = 0;
    ret = i2c_read(*dev_handle, MPU6050_WHO_AM_I, &whoAmI, 1);
    if (ret != ESP_OK || whoAmI != 0x68) {
        ESP_LOGE("MPU6050", "Failed to connect to MPU6050, Who am I: 0x%X, Error: %s", whoAmI, esp_err_to_name(ret));
        return ESP_FAIL;
    }

    // Wake up the device and enable temperature sensor
    if (i2c_write(*dev_handle, MPU6050_PWR_MGMT_1, 0x01) != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to wake up MPU6050 and enable temperature sensor, Error: 0x%X", ret);
        return ret;
    }

    // Disable I2C Master mode in USER_CTRL register
    ret = i2c_write(*dev_handle, MPU6050_USER_CTRL, 0x00);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to write USER_CTRL Register, Error: 0x%X", ret);
        return ret;
    }

    // Enable Pass-Through mode
    ret = i2c_write(*dev_handle, MPU6050_INT_PIN_CFG, 0x02);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to enable Pass-Through Mode, Error: 0x%X", ret);
        return ret;
    }

    // Set sample rate
    ret = i2c_write(*dev_handle, MPU6050_SMPLRT_DIV, 0x07);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to set Sample Rate, Error: 0x%X", ret);
        return ret;
    }

    // Configure Digital Low Pass Filter
    ret = i2c_write(*dev_handle, MPU6050_CONFIG, 0x06);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to configure Digital Low Pass Filter, Error: 0x%X", ret);
        return ret;
    }

    // Set gyroscope sensitivity
    ret = i2c_write(*dev_handle, MPU6050_GYRO_CONFIG, 0x00);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to set Gyroscope Sensitivity, Error: 0x%X", ret);
        return ret;
    }

    // Set accelerometer sensitivity
    ret = i2c_write(*dev_handle, MPU6050_ACCEL_CONFIG, 0x00);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Failed to set Accelerometer Sensitivity, Error: 0x%X", ret);
        return ret;
    }

    return ESP_OK;
}

void mpu6050_read_data(i2c_master_dev_handle_t dev_handle, mpu6050_raw_data_t *data_struct) {
    uint8_t data[14];  ///< Buffer for 14 bytes of data
    esp_err_t ret = i2c_read(dev_handle, MPU6050_ACCEL_XOUT_H, data, 14);
    if (ret == ESP_OK) {
        // Split the raw data into respective parts
        data_struct->accel_x = (int16_t)((data[0] << 8) | data[1]);
        data_struct->accel_y = (int16_t)((data[2] << 8) | data[3]);
        data_struct->accel_z = (int16_t)((data[4] << 8) | data[5]);
        data_struct->temp = (int16_t)((data[6] << 8) | data[7]);
        data_struct->gyro_x = (int16_t)((data[8] << 8) | data[9]);
        data_struct->gyro_y = (int16_t)((data[10] << 8) | data[11]);
        data_struct->gyro_z = (int16_t)((data[12] << 8) | data[13]);

        // Convert temperature to degrees Celsius
        data_struct->temp = data_struct->temp / 340.0 + 36.53;
    } else {
        ESP_LOGE("MPU6050", "Failed to read sensor data: %s", esp_err_to_name(ret));
    }
}
