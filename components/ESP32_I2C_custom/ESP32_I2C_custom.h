//
// Created by domin on 26.04.2024.
//

#ifndef ESP_TEST_MANUELL_I2C_ESP_CUSTOM_H
#define ESP_TEST_MANUELL_I2C_ESP_CUSTOM_H

#include "driver/i2c_master.h"

/**
 * @file ESP32_I2C_custom.h
 * @brief Header file for custom I2C operations on the ESP32.
 *
 * This file contains the default configurations, variable declarations, and function prototypes
 * for custom I2C operations on the ESP32 platform.
 */

// Default Configuration
#define I2C_MASTER_SCL_IO               22          ///< GPIO pin for I2C SCL
#define I2C_MASTER_SDA_IO               21          ///< GPIO pin for I2C SDA
#define I2C_MASTER_FREQ_HZ              100000      ///< I2C frequency
#define I2C_MASTER_TIMEOUT_MS           1000        ///< Timeout for I2C operations in milliseconds
#define I2C_LOG_TAG                     "I2C"       ///< Tag for ESP logging

// Variables for I2C Configuration
extern int i2c_master_scl_io;            ///< I2C SCL GPIO pin
extern int i2c_master_sda_io;            ///< I2C SDA GPIO pin
extern int i2c_master_freq_hz;           ///< I2C frequency
extern int i2c_master_timeout_ms;        ///< Timeout for I2C operations
extern const char* i2c_log_tag;          ///< Tag for ESP logging

// Setter, Getter for Configuration

/**
 * @brief Set the I2C SCL GPIO pin.
 * @param scl_io GPIO pin number for I2C SCL.
 */
void set_i2c_master_scl_io(int scl_io);

/**
 * @brief Set the I2C SDA GPIO pin.
 * @param sda_io GPIO pin number for I2C SDA.
 */
void set_i2c_master_sda_io(int sda_io);

/**
 * @brief Set the I2C frequency.
 * @param freq_hz Frequency in Hz.
 */
void set_i2c_master_freq_hz(int freq_hz);

/**
 * @brief Set the timeout for I2C operations.
 * @param timeout_ms Timeout in milliseconds.
 */
void set_i2c_master_timeout_ms(int timeout_ms);

/**
 * @brief Set the log tag for I2C operations.
 * @param log_tag Log tag string.
 */
void set_i2c_log_tag(const char* log_tag);

/**
 * @brief Get the I2C SCL GPIO pin.
 * @return GPIO pin number for I2C SCL.
 */
int get_i2c_master_scl_io();

/**
 * @brief Get the I2C SDA GPIO pin.
 * @return GPIO pin number for I2C SDA.
 */
int get_i2c_master_sda_io();

/**
 * @brief Get the I2C frequency.
 * @return Frequency in Hz.
 */
int get_i2c_master_freq_hz();

/**
 * @brief Get the timeout for I2C operations.
 * @return Timeout in milliseconds.
 */
int get_i2c_master_timeout_ms();

/**
 * @brief Get the log tag for I2C operations.
 * @return Log tag string.
 */
const char* get_i2c_log_tag();

// I2C Functions

/**
 * @brief Initialize the I2C master.
 * @param bus_handle Pointer to the I2C master bus handle.
 */
void i2c_master_init(i2c_master_bus_handle_t *bus_handle);

/**
 * @brief Scan the I2C bus for devices.
 * @param bus_handle I2C master bus handle.
 */
void i2c_scan(i2c_master_bus_handle_t bus_handle);

/**
 * @brief Write data to an I2C device.
 * @param dev_handle I2C device handle.
 * @param reg_addr Register address to write to.
 * @param reg_data Data to write to the register.
 * @return esp_err_t Error code indicating success or failure.
 */
esp_err_t i2c_write(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t reg_data);

/**
 * @brief Read data from an I2C device.
 * @param dev_handle I2C device handle.
 * @param reg_addr Register address to read from.
 * @param reg_data Pointer to buffer where read data will be stored.
 * @param length Number of bytes to read.
 * @return esp_err_t Error code indicating success or failure.
 */
esp_err_t i2c_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);



#endif //ESP_TEST_MANUELL_I2C_ESP_CUSTOM_H
