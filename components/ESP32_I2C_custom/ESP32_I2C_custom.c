//
// Created by domin on 26.04.2024.
//

#include "ESP32_I2C_custom.h"
#include "esp_log.h"

/**
 * @file ESP32_I2C_custom.c
 * @brief Implementation file for custom I2C operations on the ESP32.
 *
 * This file contains the implementation of functions for custom I2C operations on the ESP32 platform.
 */

// Variables for I2C Configuration
int i2c_master_scl_io       =   I2C_MASTER_SCL_IO;          ///< I2C SCL GPIO pin
int i2c_master_sda_io       =   I2C_MASTER_SDA_IO;          ///< I2C SDA GPIO pin
int i2c_master_freq_hz      =   I2C_MASTER_FREQ_HZ;         ///< I2C frequency
int i2c_master_timeout_ms   =   I2C_MASTER_TIMEOUT_MS;      ///< Timeout for I2C operations
const char* i2c_log_tag     =   I2C_LOG_TAG;                ///< Tag for ESP logging

// Setter functions

void set_i2c_master_scl_io(int scl_io) {
    i2c_master_scl_io = scl_io;
}

void set_i2c_master_sda_io(int sda_io) {
    i2c_master_sda_io = sda_io;
}

void set_i2c_master_freq_hz(int freq_hz) {
    i2c_master_freq_hz = freq_hz;
}

void set_i2c_master_timeout_ms(int timeout_ms) {
    i2c_master_timeout_ms = timeout_ms;
}

void set_i2c_log_tag(const char* log_tag) {
    i2c_log_tag = log_tag;
}

// Getter functions

int get_i2c_master_scl_io() {
    return i2c_master_scl_io;
}

int get_i2c_master_sda_io() {
    return i2c_master_sda_io;
}

int get_i2c_master_freq_hz() {
    return i2c_master_freq_hz;
}

int get_i2c_master_timeout_ms() {
    return i2c_master_timeout_ms;
}

const char* get_i2c_log_tag() {
    return i2c_log_tag;
}

// I2C Functions

void i2c_master_init(i2c_master_bus_handle_t *bus_handle) {
    i2c_master_bus_config_t conf = {
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .i2c_port = I2C_NUM_0,
            .sda_io_num = i2c_master_sda_io,
            .scl_io_num = i2c_master_scl_io,
            .flags.enable_internal_pullup = true
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&conf, bus_handle));
}

void i2c_scan(i2c_master_bus_handle_t bus_handle) {
    ESP_LOGI(i2c_log_tag, "Scanning I2C bus...");

    printf("    ");
    for (int i = 0; i < 16; i++) {
        printf("%3x", i);
    }
    printf("\n");

    for (int address = 0; address < 0x7F; address += 16) {
        printf("%02x:  ", address);

        for (int subaddr = 0; subaddr < 16; subaddr++) {
            int fulladdr = address + subaddr;
            esp_err_t result;

            // Perform the probe only for valid I2C addresses
            if (fulladdr <= 0x7F) {
                result = i2c_master_probe(bus_handle, fulladdr, 1000);
            } else {
                // Directly mark addresses outside the valid range as non-present
                result = ESP_ERR_INVALID_ARG;
            }

            if (result == ESP_OK) {
                printf(" X ");
            } else {
                printf(" . ");
            }
        }
        printf("\n");
    }

    ESP_LOGI(i2c_log_tag, "I2C scan finished.");
}

esp_err_t i2c_write(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t reg_data) {
    uint8_t data[2] = {reg_addr, reg_data}; // Create an array for register address and data

    // Perform the I2C write operation
    esp_err_t err = i2c_master_transmit(dev_handle, data, sizeof(data), I2C_MASTER_TIMEOUT_MS);

    if (err != ESP_OK) {
        ESP_LOGE(i2c_log_tag, "I2C write failed: %s", esp_err_to_name(err));
    }
    return err;
}

esp_err_t i2c_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *reg_data, uint32_t length) {
    // Send only the register address
    esp_err_t err = i2c_master_transmit_receive(dev_handle, &reg_addr, 1, reg_data, length, I2C_MASTER_TIMEOUT_MS);
    if (err != ESP_OK) {
        ESP_LOGE(i2c_log_tag, "I2C read failed: %s", esp_err_to_name(err));
    }
    return err;
}
