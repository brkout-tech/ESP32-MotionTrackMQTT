//
// Created by domin on 20.05.2024.
//

#ifndef ESP_GYRO_MS5611_BARO_DEFS_H
#define ESP_GYRO_MS5611_BARO_DEFS_H

#include "stdint.h"

/**
 * @file ms5611_baro_defs.h
 * @brief Definitions for MS5611 Barometer Sensor.
 *
 * This file contains the register addresses, commands, and data structures used
 * for interacting with the MS5611 barometer sensor.
 */

/* MS5611 I2C address */
#define MS5611_I2C_ADDRESS 0x77  ///< MS5611 I2C address (can also be 0x76 depending on connection)

/********************************************************* */
/*!               Register Map Addresses                 */
/********************************************************* */

/* Reset Command */
#define MS5611_CMD_RESET 0x1E  ///< Reset command

/* Conversion Commands */
#define MS5611_CMD_CONVERT_D1 0x40  ///< Pressure conversion command
#define MS5611_CMD_CONVERT_D2 0x50  ///< Temperature conversion command

/* Read ADC Result */
#define MS5611_CMD_READ_ADC 0x00  ///< Read ADC result command

/* PROM Read */
#define MS5611_CMD_READ_PROM_BASE 0xA0  ///< Base address for PROM read, increment by 2 for each next

/********************************************************* */
/*!               Calibration Coefficients                */
/********************************************************* */

#define MS5611_PROM_C1 0xA2  ///< Pressure sensitivity coefficient
#define MS5611_PROM_C2 0xA4  ///< Pressure offset coefficient
#define MS5611_PROM_C3 0xA6  ///< Temperature coefficient of pressure sensitivity
#define MS5611_PROM_C4 0xA8  ///< Temperature coefficient of pressure offset
#define MS5611_PROM_C5 0xAA  ///< Reference temperature
#define MS5611_PROM_C6 0xAC  ///< Temperature coefficient of temperature

/********************************************************* */
/*!               Data Structures                         */
/********************************************************* */

/**
 * @brief Structure to hold the calibration coefficients
 */
typedef struct {
    uint16_t C1;  ///< Pressure sensitivity coefficient
    uint16_t C2;  ///< Pressure offset coefficient
    uint16_t C3;  ///< Temperature coefficient of pressure sensitivity
    uint16_t C4;  ///< Temperature coefficient of pressure offset
    uint16_t C5;  ///< Reference temperature
    uint16_t C6;  ///< Temperature coefficient of temperature
} ms5611_calib_data_t;

/**
 * @brief Structure to hold the raw pressure and temperature data
 */
typedef struct {
    uint32_t raw_pressure;    ///< Raw pressure data
    uint32_t raw_temperature; ///< Raw temperature data
} ms5611_raw_data_t;

/**
 * @brief Structure to hold the processed pressure and temperature data
 */
typedef struct {
    float temperature;  ///< Temperature in degrees Celsius
    float pressure;     ///< Pressure in millibars
} ms5611_data_t;

#endif //ESP_GYRO_MS5611_BARO_DEFS_H
