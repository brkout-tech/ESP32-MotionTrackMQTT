# ESP32 GY-86 Sensor Suite Project

## Overview

This project demonstrates the use of the GY-86 sensor suite with an ESP32 microcontroller. The GY-86 sensor suite includes sensors for temperature, pressure, acceleration, orientation, and compass direction. The project uses headers of the ESP-IDF and custom I2C, WiFi, and MQTT components to read data from the sensors and publish it to an MQTT broker.

## Project Structure

```
ESP32_GY86_Project/
├── CMakeLists.txt
├── components/
│ ├── ESP32_I2C_custom/
│ │ ├── CMakeLists.txt
│ │ ├── ESP32_I2C_custom.c
│ │ ├── ESP32_I2C_custom.h
│ ├── ESP32_Mqtt_custom/
│ │ ├── CMakeLists.txt
│ │ ├── ESP32_Mqtt_custom.c
│ │ ├── ESP32_Mqtt_custom.h
│ │ ├── ESP32_Mqtt_custom_defs.h
│ ├── ESP32_Wifi_custom/
│ │ ├── CMakeLists.txt
│ │ ├── ESP32_Wifi_custom.c
│ │ ├── ESP32_Wifi_custom.h
│ ├── GY-86/
│ │ ├── CMakeLists.txt
│ │ ├── gy86_data.c
│ │ ├── gy86_data.h
│ │ ├── gy86_data_defs.h
│ ├── MPU6050/
│ │ ├── CMakeLists.txt
│ │ ├── mpu6050_gyro_accel.c
│ │ ├── mpu6050_gyro_accel.h
│ │ ├── mpu6050_gyro_accel_defs.h
│ ├── MS5611/
│ │ ├── CMakeLists.txt
│ │ ├── ms5611_baro.c
│ │ ├── ms5611_baro.h
│ │ ├── ms5611_baro_defs.h
│ ├── HMC5883L/
│ │ ├── CMakeLists.txt
│ │ ├── hmc5883L_compas.c
│ │ ├── hmc5883L_compas.h
│ │ ├── hmc5883L_compas_defs.h
├── main/
│ ├── CMakeLists.txt
│ ├── main.c
```

## Getting Started

### Prerequisites

- ESP-IDF (Espressif IoT Development Framework)
- CLion or other compatible IDE

## Project Components

### ESP32 I2C Custom Component

This component handles I2C communication with the sensors.

- **Source Files:**
    - `ESP32_I2C_custom.c`
    - `ESP32_I2C_custom.h`

### ESP32 MQTT Custom Component

This component handles MQTT communication.

- **Source Files:**
    - `ESP32_Mqtt_custom.c`
    - `ESP32_Mqtt_custom.h`
    - `ESP32_Mqtt_custom_defs.h`

### ESP32 WiFi Custom Component

This component handles WiFi initialization and connection.

- **Source Files:**
    - `ESP32_Wifi_custom.c`
    - `ESP32_Wifi_custom.h`

### GY-86 Sensor Suite Component

This component handles data collection and processing from the GY-86 sensors.

- **Source Files:**
    - `gy86_data.c`
    - `gy86_data.h`
    - `gy86_data_defs.h`

### Sensor-Specific Components

- **MPU6050 (Gyroscope and Accelerometer):**
    - `mpu6050_gyro_accel.c`
    - `mpu6050_gyro_accel.h`
    - `mpu6050_gyro_accel_defs.h`

- **MS5611 (Barometer):**
    - `ms5611_baro.c`
    - `ms5611_baro.h`
    - `ms5611_baro_defs.h`

- **HMC5883L (Compass):**
    - `hmc5883L_compas.c`
    - `hmc5883L_compas.h`
    - `hmc5883L_compas_defs.h`

## Main Application

The main application initializes the I2C bus, GY-86 sensors, WiFi, and MQTT. It then enters a loop where it periodically reads sensor data and publishes it to an MQTT broker.

- **Source File:**
    - `main.c`

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.