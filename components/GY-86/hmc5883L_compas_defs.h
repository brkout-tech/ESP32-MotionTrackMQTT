//
// Created by domin on 20.05.2024.
//

#ifndef ESP_GYRO_HMC5883L_COMPAS_DEFS_H
#define ESP_GYRO_HMC5883L_COMPAS_DEFS_H

#include "stdint.h"

/**
 * @file hmc5883L_compas_defs.h
 * @brief Definitions for HMC5883L Compass Sensor.
 *
 * This file contains the register addresses, commands, and data structures used
 * for interacting with the HMC5883L compass sensor.
 */

/* HMC5883L I2C address */
#define HMC5883L_I2C_ADDRESS 0x1E  ///< HMC5883L I2C address

/********************************************************* */
/*!               Register Map Addresses                 */
/********************************************************* */

/* Configuration Registers */
#define HMC5883L_CONFIG_A 0x00  ///< Configuration Register A
#define HMC5883L_CONFIG_B 0x01  ///< Configuration Register B
#define HMC5883L_MODE_REGISTER 0x02  ///< Mode Register

/* Data Registers */
#define HMC5883L_DATA_X_MSB 0x03  ///< Data X MSB Register
#define HMC5883L_DATA_X_LSB 0x04  ///< Data X LSB Register
#define HMC5883L_DATA_Z_MSB 0x05  ///< Data Z MSB Register
#define HMC5883L_DATA_Z_LSB 0x06  ///< Data Z LSB Register
#define HMC5883L_DATA_Y_MSB 0x07  ///< Data Y MSB Register
#define HMC5883L_DATA_Y_LSB 0x08  ///< Data Y LSB Register

/* Status Register */
#define HMC5883L_STATUS 0x09  ///< Status Register

/* Identification Registers */
#define HMC5883L_ID_A 0x0A  ///< Identification Register A
#define HMC5883L_ID_B 0x0B  ///< Identification Register B
#define HMC5883L_ID_C 0x0C  ///< Identification Register C

/********************************************************* */
/*!               Configuration Values                   */
/********************************************************* */

/* Mode Register Values */
#define HMC5833L_ENABLE_HIGHSPEED 0b10000000  ///< Enable high-speed I2C
#define HMC5883L_CONTINUOUS_MEASUREMENT_MODE 0b00000000  ///< Continuous measurement mode
#define HMC5883L_SINGLE_MEASUREMENT_MODE 0b00100000  ///< Single measurement mode
#define HMC5883L_IDLE_MODE 0b01000000  ///< Idle mode

/* Number of samples averaged per measurement output */
#define HMC5883L_AVERAGING_1 0x00  ///< 1 sample averaged per measurement output (default)
#define HMC5883L_AVERAGING_2 0x20  ///< 2 samples averaged per measurement output
#define HMC5883L_AVERAGING_4 0x40  ///< 4 samples averaged per measurement output
#define HMC5883L_AVERAGING_8 0x60  ///< 8 samples averaged per measurement output

/* Configuration Register A Data Output Rate Bits */
#define HMC5883L_DATA_RATE_0_75_HZ 0x00  ///< Data output rate 0.75 Hz
#define HMC5883L_DATA_RATE_1_5_HZ 0x04  ///< Data output rate 1.5 Hz
#define HMC5883L_DATA_RATE_3_0_HZ 0x08  ///< Data output rate 3.0 Hz
#define HMC5883L_DATA_RATE_7_5_HZ 0x0C  ///< Data output rate 7.5 Hz
#define HMC5883L_DATA_RATE_15_HZ 0x10  ///< Data output rate 15 Hz (default)
#define HMC5883L_DATA_RATE_30_HZ 0x14  ///< Data output rate 30 Hz
#define HMC5883L_DATA_RATE_75_HZ 0x18  ///< Data output rate 75 Hz

/* Configuration Register A Measurement Configuration Bits */
#define HMC5883L_NORMAL_MEASUREMENT_CONFIGURATION 0x00  ///< Normal measurement configuration
#define HMC5883L_POSITIVE_BIAS_CONFIGURATION 0x01  ///< Positive bias configuration
#define HMC5883L_NEGATIVE_BIAS_CONFIGURATION 0x02  ///< Negative bias configuration

/* Configuration Register B Gain Settings */
#define HMC5883L_GAIN_1370 0b00000000  ///< Gain 1370 (0.73 mG/LSb)
#define HMC5883L_GAIN_1090 0b00100000  ///< Gain 1090 (0.92 mG/LSb, default)
#define HMC5883L_GAIN_820 0b01000000  ///< Gain 820 (1.22 mG/LSb)
#define HMC5883L_GAIN_660 0b01100000  ///< Gain 660 (1.52 mG/LSb)
#define HMC5883L_GAIN_440 0b10000000  ///< Gain 440 (2.27 mG/LSb)
#define HMC5883L_GAIN_390 0b10100000  ///< Gain 390 (2.56 mG/LSb)
#define HMC5883L_GAIN_330 0b11000000  ///< Gain 330 (3.03 mG/LSb)
#define HMC5883L_GAIN_230 0b11100000  ///< Gain 230 (4.35 mG/LSb)

/********************************************************* */
/*!               Data Structures                         */
/********************************************************* */

/**
 * @brief Structure to hold the raw magnetometer data
 */
typedef struct {
    int16_t x;  ///< Raw X-axis data
    int16_t y;  ///< Raw Y-axis data
    int16_t z;  ///< Raw Z-axis data
} hmc5883l_raw_data_t;

/**
 * @brief Structure to hold the processed magnetometer data
 */
typedef struct {
    float x;  ///< Processed X-axis data
    float y;  ///< Processed Y-axis data
    float z;  ///< Processed Z-axis data
} hmc5883l_data_t;

#endif //ESP_GYRO_HMC5883L_COMPAS_DEFS_H
