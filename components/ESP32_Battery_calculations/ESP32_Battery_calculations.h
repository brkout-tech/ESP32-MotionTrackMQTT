// ESP32_Battery_calculations.h
//
// Created by domin on 26.04.2024.
//

#ifndef ESP_TEST_MANUELL_BATTERY_H
#define ESP_TEST_MANUELL_BATTERY_H

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

/**
 * @file ESP32_Battery_calculations.h
 * @brief Header file for battery voltage and percentage calculations on the ESP32.
 *
 * This file contains the default configurations, variable declarations, and function prototypes
 * for battery voltage and percentage calculations on the ESP32 platform.
 */

// Default Configuration
#define BATTERY_ADC_UNIT_ID                 ADC_UNIT_1          ///< ADC unit ID
#define BATTERY_ADC_ULP_MODE                ADC_ULP_MODE_DISABLE///< ADC ULP mode
#define BATTERY_ADC_BITWIDTH                ADC_BITWIDTH_DEFAULT///< ADC bit width
#define BATTERY_ADC_ATTEN                   ADC_ATTEN_DB_12     ///< ADC attenuation
#define BATTERY_ADC_CHANNEL                 ADC_CHANNEL_6       ///< ADC channel
#define BATTERY_MAX_VOLTAGE                 4200                ///< Maximum battery voltage in mV
#define BATTERY_MIN_VOLTAGE                 3500                ///< Minimum battery voltage in mV
#define BATTERY_VOLTAGE_MULTIPLIER          2                   ///< Multiplier for the voltage divider at ADC input
#define BATTERY_LOG_TAG                     "BATTERY"           ///< Tag for ESP logging

#define BATTERY_PERCENTAGE_FACTOR (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE) ///< Factor for battery percentage calculation

// Setter, Getter for Configuration

/**
 * @brief Set the ADC unit ID.
 * @param unit_id ADC unit ID.
 */
void set_battery_adc_unit_id(int unit_id);

/**
 * @brief Set the ADC ULP mode.
 * @param ulp_mode ADC ULP mode.
 */
void set_battery_adc_ulp_mode(int ulp_mode);

/**
 * @brief Set the ADC bit width.
 * @param bitwidth ADC bit width.
 */
void set_battery_adc_bitwidth(int bitwidth);

/**
 * @brief Set the ADC attenuation.
 * @param atten ADC attenuation.
 */
void set_battery_adc_atten(int atten);

/**
 * @brief Set the ADC channel.
 * @param channel ADC channel.
 */
void set_battery_adc_channel(int channel);

/**
 * @brief Set the maximum battery voltage.
 * @param max_voltage Maximum battery voltage in mV.
 */
void set_battery_max_voltage(int max_voltage);

/**
 * @brief Set the minimum battery voltage.
 * @param min_voltage Minimum battery voltage in mV.
 */
void set_battery_min_voltage(int min_voltage);

/**
 * @brief Set the voltage multiplier.
 * @param multiplier Voltage multiplier.
 */
void set_battery_voltage_multiplier(int multiplier);

/**
 * @brief Set the log tag for battery operations.
 * @param log_tag Log tag string.
 */
void set_battery_log_tag(const char* log_tag);

/**
 * @brief Get the ADC unit ID.
 * @return ADC unit ID.
 */
int get_battery_adc_unit_id();

/**
 * @brief Get the ADC ULP mode.
 * @return ADC ULP mode.
 */
int get_battery_adc_ulp_mode();

/**
 * @brief Get the ADC bit width.
 * @return ADC bit width.
 */
int get_battery_adc_bitwidth();

/**
 * @brief Get the ADC attenuation.
 * @return ADC attenuation.
 */
int get_battery_adc_atten();

/**
 * @brief Get the ADC channel.
 * @return ADC channel.
 */
int get_battery_adc_channel();

/**
 * @brief Get the maximum battery voltage.
 * @return Maximum battery voltage in mV.
 */
int get_battery_max_voltage();

/**
 * @brief Get the minimum battery voltage.
 * @return Minimum battery voltage in mV.
 */
int get_battery_min_voltage();

/**
 * @brief Get the voltage multiplier.
 * @return Voltage multiplier.
 */
int get_battery_voltage_multiplier();

/**
 * @brief Get the log tag for battery operations.
 * @return Log tag string.
 */
const char* get_battery_log_tag();

// Functions

/**
 * @brief Initialize ADC calibration.
 */
void init_adc_calibration(void);

/**
 * @brief Read the battery voltage.
 * @return Battery voltage in mV.
 */
uint32_t read_battery_voltage(void);

/**
 * @brief Calculate the battery percentage.
 * @param battery_voltage Battery voltage in mV.
 * @return Battery percentage.
 */
uint8_t calc_battery_percentage(uint32_t battery_voltage);

#endif //ESP_TEST_MANUELL_BATTERY_H
