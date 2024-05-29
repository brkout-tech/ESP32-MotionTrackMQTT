//
// Created by domin on 15.05.2024.
//

#include "ms5611_baro.h"
#include "ms5611_baro_defs.h"
#include "../ESP32_I2C_custom/ESP32_I2C_custom.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

/**
 * @file ms5611_baro.c
 * @brief Implementation file for MS5611 Barometer Sensor functions.
 *
 * This file contains the implementation of functions for initializing and interacting with the MS5611 barometer sensor.
 */

static ms5611_calib_data_t calib_data;  ///< Calibration data for the MS5611 sensor

/**
 * @brief Read calibration coefficients from the MS5611 sensor PROM.
 * @param dev_handle I2C device handle.
 * @return esp_err_t ESP_OK on success, or an error code on failure.
 */
static esp_err_t ms5611_read_prom(i2c_master_dev_handle_t dev_handle) {
    uint16_t *calib_coefficients = (uint16_t *)&calib_data;
    uint8_t data[2];
    esp_err_t err;

    for (int i = 0; i < 6; i++) {
        uint8_t cmd = MS5611_PROM_C1 + (i * 2);
        err = i2c_read(dev_handle, cmd, data, 2);
        if (err != ESP_OK) return err;
        calib_coefficients[i] = (data[0] << 8) | data[1];
    }
    return ESP_OK;
}

esp_err_t ms5611_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = MS5611_I2C_ADDRESS,
            .scl_speed_hz = 100000,
    };

    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (ret != ESP_OK) {
        ESP_LOGE("MS5611", "Failed to add MS5611 device: %s", esp_err_to_name(ret));
        return ret;
    }

    // Reset the device
    ms5611_reset(*dev_handle);
    vTaskDelay(pdMS_TO_TICKS(10));  // Wait after reset

    // Read calibration coefficients
    ret = ms5611_read_prom(*dev_handle);
    if (ret != ESP_OK) {
        ESP_LOGE("MS5611", "Failed to read PROM: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}

void ms5611_reset(i2c_master_dev_handle_t dev_handle) {
    i2c_write(dev_handle, MS5611_CMD_RESET, 0);
    vTaskDelay(pdMS_TO_TICKS(3)); // Wait for the reset sequence to complete
}

/**
 * @brief Start a conversion on the MS5611 sensor.
 * @param dev_handle I2C device handle.
 * @param cmd Conversion command (MS5611_CMD_CONVERT_D1 or MS5611_CMD_CONVERT_D2).
 * @return esp_err_t ESP_OK on success, or an error code on failure.
 */
esp_err_t ms5611_start_conversion(i2c_master_dev_handle_t dev_handle, uint8_t cmd) {
    return i2c_write(dev_handle, cmd, 0);
}

/**
 * @brief Read the ADC value from the MS5611 sensor.
 * @param dev_handle I2C device handle.
 * @return uint32_t ADC value.
 */
uint32_t ms5611_read_adc(i2c_master_dev_handle_t dev_handle) {
    uint8_t data[3];
    if (i2c_read(dev_handle, MS5611_CMD_READ_ADC, data, 3) != ESP_OK) {
        ESP_LOGE("MS5611", "Failed to read ADC");
        return 0;  // On error, return 0
    }
    return (data[0] << 16) | (data[1] << 8) | data[2];
}

esp_err_t ms5611_read_pressure_and_temperature(i2c_master_dev_handle_t dev_handle, ms5611_data_t *data) {
    // Start pressure conversion
    ms5611_start_conversion(dev_handle, MS5611_CMD_CONVERT_D1);
    vTaskDelay(pdMS_TO_TICKS(10)); // Wait for conversion time
    uint32_t D1 = ms5611_read_adc(dev_handle); // Read pressure data

    // Start temperature conversion
    ms5611_start_conversion(dev_handle, MS5611_CMD_CONVERT_D2);
    vTaskDelay(pdMS_TO_TICKS(10)); // Wait for conversion time
    uint32_t D2 = ms5611_read_adc(dev_handle); // Read temperature data

    if (D1 == 0 || D2 == 0) {
        return ESP_FAIL;
    }

    // Temperature calculation
    int32_t dT = D2 - (calib_data.C5 * 256);
    int32_t TEMP = 2000 + ((int64_t)dT * calib_data.C6 / 8388608);

    // Pressure calculation
    int64_t OFF = (int64_t)calib_data.C2 * 65536 + (int64_t)calib_data.C4 * dT / 128;
    int64_t SENS = (int64_t)calib_data.C1 * 32768 + (int64_t)calib_data.C3 * dT / 256;
    int32_t P = (D1 * SENS / 2097152 - OFF) / 32768;

    data->temperature = TEMP / 100.0;
    data->pressure = P / 100.0;
    return ESP_OK;
}
