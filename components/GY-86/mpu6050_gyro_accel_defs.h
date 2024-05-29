//
// Created by domin on 17.05.2024.
//

#ifndef ESP_GYRO_MPU6050_GYRO_ACCEL_DEFS_H
#define ESP_GYRO_MPU6050_GYRO_ACCEL_DEFS_H

#include "stdint.h"

/**
 * @file mpu6050_gyro_accel_defs.h
 * @brief Definitions for MPU6050 Gyroscope and Accelerometer Sensor.
 *
 * This file contains the register addresses, commands, and data structures used
 * for interacting with the MPU6050 gyroscope and accelerometer sensor.
 */

/* MPU6050 I2C address */
#define MPU6050_I2C_ADDRESS 0x68  ///< MPU6050 I2C address

/********************************************************* */
/*!               Register Map Addresses                 */
/********************************************************* */

/* Self Test Registers */
#define MPU6050_SELF_TEST_X 0x0D          ///< Self Test X register
#define MPU6050_SELF_TEST_Y 0x0E          ///< Self Test Y register
#define MPU6050_SELF_TEST_Z 0x0F          ///< Self Test Z register
#define MPU6050_SELF_TEST_A 0x10          ///< Self Test A register

/* Sample Rate Divider */
#define MPU6050_SMPLRT_DIV 0x19           ///< Sample Rate Divider register

/* Configuration */
#define MPU6050_CONFIG 0x1A               ///< Configuration register
#define MPU6050_GYRO_CONFIG 0x1B          ///< Gyroscope Configuration register
#define MPU6050_ACCEL_CONFIG 0x1C         ///< Accelerometer Configuration register

/* I2C Master Enable Bit */
#define I2C_MST_EN 0x20                   ///< I2C Master Enable bit

/* FIFO Enable */
#define MPU6050_FIFO_EN 0x23              ///< FIFO Enable register

/* I2C Master Control */
#define MPU6050_I2C_MST_CTRL 0x24         ///< I2C Master Control register

/* I2C Slave 0 Control */
#define MPU6050_I2C_SLV0_ADDR 0x25       ///< I2C Slave 0 Address register
#define MPU6050_I2C_SLV0_REG 0x26        ///< I2C Slave 0 Register
#define MPU6050_I2C_SLV0_CTRL 0x27       ///< I2C Slave 0 Control register

/* I2C Slave 1 Control */
#define MPU6050_I2C_SLV1_ADDR 0x28       ///< I2C Slave 1 Address register
#define MPU6050_I2C_SLV1_REG 0x29        ///< I2C Slave 1 Register
#define MPU6050_I2C_SLV1_CTRL 0x2A       ///< I2C Slave 1 Control register

/* I2C Slave 4 Control */
#define MPU6050_I2C_SLV4_CTRL 0x34       ///< I2C Slave 4 Control register

/* I2C Master Status */
#define MPU6050_I2C_MST_STATUS 0x36      ///< I2C Master Status register

/* INT Pin / Bypass Enable Configuration */
#define MPU6050_INT_PIN_CFG 0x37         ///< INT Pin / Bypass Enable Configuration register

/* INT Enable */
#define MPU6050_INT_ENABLE 0x38  ///< INT Enable register

/* INT Status */
#define MPU6050_INT_STATUS 0x3A  ///< INT Status register

/* Accelerometer and Gyroscope Registers */
#define MPU6050_ACCEL_XOUT_H 0x3B  ///< Accelerometer X-axis High byte
#define MPU6050_ACCEL_XOUT_L 0x3C  ///< Accelerometer X-axis Low byte
#define MPU6050_ACCEL_YOUT_H 0x3D  ///< Accelerometer Y-axis High byte
#define MPU6050_ACCEL_YOUT_L 0x3E  ///< Accelerometer Y-axis Low byte
#define MPU6050_ACCEL_ZOUT_H 0x3F  ///< Accelerometer Z-axis High byte
#define MPU6050_ACCEL_ZOUT_L 0x40  ///< Accelerometer Z-axis Low byte
#define MPU6050_TEMP_OUT_H 0x41  ///< Temperature High byte
#define MPU6050_TEMP_OUT_L 0x42  ///< Temperature Low byte
#define MPU6050_GYRO_XOUT_H 0x43  ///< Gyroscope X-axis High byte
#define MPU6050_GYRO_XOUT_L 0x44  ///< Gyroscope X-axis Low byte
#define MPU6050_GYRO_YOUT_H 0x45  ///< Gyroscope Y-axis High byte
#define MPU6050_GYRO_YOUT_L 0x46  ///< Gyroscope Y-axis Low byte
#define MPU6050_GYRO_ZOUT_H 0x47  ///< Gyroscope Z-axis High byte
#define MPU6050_GYRO_ZOUT_L 0x48  ///< Gyroscope Z-axis Low byte

/* External Sensor Data */
#define MPU6050_EXT_SENS_DATA_00 0x49  ///< External Sensor Data register

/* I2C Slave Data Out */
#define MPU6050_I2C_SLV0_DO 0x63  ///< I2C Slave 0 Data Out register

/* Signal Path Reset */
#define MPU6050_SIGNAL_PATH_RESET 0x68  ///< Signal Path Reset register

/* User Control */
#define MPU6050_USER_CTRL 0x6A  ///< User Control register

/* Power Management */
#define MPU6050_PWR_MGMT_1 0x6B  ///< Power Management 1 register
#define MPU6050_PWR_MGMT_2 0x6C  ///< Power Management 2 register

/* FIFO Count Registers */
#define MPU6050_FIFO_COUNTH 0x72  ///< FIFO Count High byte
#define MPU6050_FIFO_COUNTL 0x73  ///< FIFO Count Low byte

/* FIFO Read Write */
#define MPU6050_FIFO_R_W 0x74  ///< FIFO Read Write register

/* WHO_AM_I */
#define MPU6050_WHO_AM_I 0x75  ///< WHO_AM_I register

/* Data Length */
#define MPU6050_DATA_LENGTH 14  ///< Data length for accelerometer and gyroscope readings

/********************************************************* */
/*!               Data Structures                         */
/********************************************************* */

/**
 * @brief Structure to hold the raw accelerometer and gyroscope data
 */
typedef struct {
    int16_t accel_x;  ///< Raw accelerometer X-axis data
    int16_t accel_y;  ///< Raw accelerometer Y-axis data
    int16_t accel_z;  ///< Raw accelerometer Z-axis data
    double temp;      ///< Temperature data
    int16_t gyro_x;   ///< Raw gyroscope X-axis data
    int16_t gyro_y;   ///< Raw gyroscope Y-axis data
    int16_t gyro_z;   ///< Raw gyroscope Z-axis data
} mpu6050_raw_data_t;

/**
 * @brief Structure to hold the processed accelerometer and gyroscope data
 */
typedef struct {
    float accel_x;  ///< Processed accelerometer X-axis data
    float accel_y;  ///< Processed accelerometer Y-axis data
    float accel_z;  ///< Processed accelerometer Z-axis data
    float temp;     ///< Temperature data in degrees Celsius
    float gyro_x;   ///< Processed gyroscope X-axis data
    float gyro_y;   ///< Processed gyroscope Y-axis data
    float gyro_z;   ///< Processed gyroscope Z-axis data
} mpu6050_data_t;

#endif //ESP_GYRO_MPU6050_GYRO_ACCEL_DEFS_H
