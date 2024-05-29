idf_component_register(SRCS "mpu6050_gyro_accel.c" "ms5611_baro.c" "hmc5883L_compas.c" "gy86_data.c"
        INCLUDE_DIRS "."
        REQUIRES driver)