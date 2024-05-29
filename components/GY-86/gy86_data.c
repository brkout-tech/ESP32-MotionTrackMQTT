//
// Created by domin on 20.05.2024.
//

#include "gy86_data.h"
#include "mpu6050_gyro_accel.h"
#include "ms5611_baro.h"
#include "hmc5883L_compas.h"
#include "math.h"
#include "esp_log.h"



mpu6050_raw_data_t mpu6050RawData;
i2c_master_dev_handle_t mpu6050_dev_handle;

ms5611_data_t ms5611RawData;
i2c_master_dev_handle_t ms5611_dev_handle;

hmc5883l_raw_data_t hmc5883LRawData;
i2c_master_dev_handle_t hmc5883l_dev_handle;

/**
 * @file gy86_data.c
 * @brief Implementation file for GY-86 Sensor Suite functions.
 *
 * This file contains the implementation of functions for initializing and interacting with the GY-86 sensor suite,
 * including functions for reading data from the sensors, calculating altitude, orientation, and heading.
 */

void init_gy86_module(i2c_master_bus_handle_t bus_handle) {
    if (mpu6050_init(bus_handle, &mpu6050_dev_handle) == ESP_OK) {
        ESP_LOGI("MPU6050", "INIT Done!");
    } else {
        ESP_LOGE("MPU6050", "INIT Failed!");
    }

    if (ms5611_init(bus_handle, &ms5611_dev_handle) == ESP_OK) {
        ESP_LOGI("MS5611", "INIT Done!");
    } else {
        ESP_LOGE("MS5611", "INIT Failed!");
    }

    if (hmc5883l_init(bus_handle, &hmc5883l_dev_handle) == ESP_OK) {
        ESP_LOGI("HMC5883L", "INIT Done!");
    } else {
        ESP_LOGE("HMC5883L", "INIT Failed!");
    }
}

float calculate_altitude(float pressure_mbar) {
    return 44330.0 * (1.0 - pow(pressure_mbar / SEA_LEVEL_PRESSURE_HPA, 0.1903));
}

sensor_orientation_t calculate_orientation(const mpu6050_raw_data_t *data) {
    sensor_orientation_t orientation;

    // Calculate the angles in radians and then convert to degrees
    float ax = data->accel_x;
    float ay = data->accel_y;
    float az = data->accel_z;

    // Avoid division by zero and ensure the value range is safe for asin()
    float axz = sqrt(ax * ax + az * az);
    float ayz = sqrt(ay * ay + az * az);

    // Calculate pitch and roll
    if (axz != 0.0f) {
        orientation.pitch = atan(ay / axz) * 180.0 / PI;
    } else {
        orientation.pitch = (ay > 0 ? 90.0 : -90.0);
    }

    if (ayz != 0.0f) {
        orientation.roll = atan(ax / ayz) * 180.0 / PI;
    } else {
        orientation.roll = (ax > 0 ? 90.0 : -90.0);
    }

    return orientation;
}

// TODO: Inclination does not work
float calculate_heading(const hmc5883l_raw_data_t *mag_data, const mpu6050_raw_data_t *accel_data) {
    float heading;
    float roll, pitch;
    float xh, yh;

    // Calculate pitch and roll angles
    roll = atan2(accel_data->accel_y, accel_data->accel_z);
    pitch = atan2(-accel_data->accel_x, sqrt(accel_data->accel_y * accel_data->accel_y + accel_data->accel_z * accel_data->accel_z));

    // Tilt compensation for magnetometer X and Y coordinates
    xh = mag_data->x * cos(pitch) + mag_data->z * sin(pitch);
    yh = mag_data->x * sin(roll) * sin(pitch) + mag_data->y * cos(roll) - mag_data->z * sin(roll) * cos(pitch);

    // Calculate azimuth
    heading = atan2(yh, xh) * RAD_TO_DEG;
    if (heading < 0) {
        heading += 360;
    }

    return heading;
}

/**
 * @brief Get the compass direction based on the heading.
 * @param heading Heading in degrees.
 * @return Compass direction as a string.
 */
const char* get_compass_direction(float heading) {
    if (heading < 0) {
        heading += 360;  // Ensure the angle is positive
    }

    if ((heading >= 337.5) || (heading < 22.5)) {
        return "N";  // North
    } else if (heading < 67.5) {
        return "NE";  // Northeast
    } else if (heading < 112.5) {
        return "E";  // East
    } else if (heading < 157.5) {
        return "SE";  // Southeast
    } else if (heading < 202.5) {
        return "S";  // South
    } else if (heading < 247.5) {
        return "SW";  // Southwest
    } else if (heading < 292.5) {
        return "W";  // West
    } else {
        return "NW";  // Northwest
    }
}

/**
 * @brief Update the sensor data for the GY-86 sensor suite.
 */
void update_sensor_data() {
    mpu6050_read_data(mpu6050_dev_handle, &mpu6050RawData);
    ms5611_read_pressure_and_temperature(ms5611_dev_handle, &ms5611RawData);
    hmc5883l_read_data(hmc5883l_dev_handle, &hmc5883LRawData);

    // Process the raw data
    sensor_orientation_t orientation = calculate_orientation(&mpu6050RawData);
    float altitude = calculate_altitude(ms5611RawData.pressure);
    float direction = calculate_heading(&hmc5883LRawData, &mpu6050RawData);
    const char *compass = get_compass_direction(direction);

    sensor_data_array[0].value.float_value = ms5611RawData.temperature;
    sensor_data_array[1].value.float_value = ms5611RawData.pressure;
    sensor_data_array[2].value.float_value = orientation.roll;
    sensor_data_array[3].value.float_value = orientation.pitch;
    sensor_data_array[4].value.float_value = altitude;
    sensor_data_array[5].value.float_value = direction;
    sensor_data_array[6].value.string_value = compass;
    sensor_data_array[7].value.int_value = mpu6050RawData.accel_x;
    sensor_data_array[8].value.int_value = mpu6050RawData.accel_y;
    sensor_data_array[9].value.int_value = mpu6050RawData.accel_z;
}

sensor_data_t* get_sensor_data(int *count) {
    update_sensor_data();
    *count = sizeof(sensor_data_array) / sizeof(sensor_data_array[0]);
    return sensor_data_array;
}
