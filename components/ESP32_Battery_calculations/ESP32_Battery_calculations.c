// ESP32_Battery_calculations.c
//
// Created by domin on 26.04.2024.
//

#include "ESP32_Battery_calculations.h"
#include "esp_log.h"


/// Variables for Battery Configuration
static int battery_adc_unit_id = BATTERY_ADC_UNIT_ID;
static int battery_adc_ulp_mode = BATTERY_ADC_ULP_MODE;
static int battery_adc_bitwidth = BATTERY_ADC_BITWIDTH;
static int battery_adc_atten = BATTERY_ADC_ATTEN;
static int battery_adc_channel = BATTERY_ADC_CHANNEL;
static int battery_max_voltage = BATTERY_MAX_VOLTAGE;
static int battery_min_voltage = BATTERY_MIN_VOLTAGE;
static int battery_voltage_multiplier = BATTERY_VOLTAGE_MULTIPLIER;
static const char *battery_log_tag = BATTERY_LOG_TAG;

static adc_oneshot_unit_handle_t adc1_handle = NULL;
static adc_cali_handle_t adc_cali_handle = NULL;

// Setter functions
void set_battery_adc_unit_id(int unit_id) {
    battery_adc_unit_id = unit_id;
}

void set_battery_adc_ulp_mode(int ulp_mode) {
    battery_adc_ulp_mode = ulp_mode;
}

void set_battery_adc_bitwidth(int bitwidth) {
    battery_adc_bitwidth = bitwidth;
}

void set_battery_adc_atten(int atten) {
    battery_adc_atten = atten;
}

void set_battery_adc_channel(int channel) {
    battery_adc_channel = channel;
}

void set_battery_max_voltage(int max_voltage) {
    battery_max_voltage = max_voltage;
}

void set_battery_min_voltage(int min_voltage) {
    battery_min_voltage = min_voltage;
}

void set_battery_voltage_multiplier(int multiplier) {
    battery_voltage_multiplier = multiplier;
}

void set_battery_log_tag(const char* log_tag) {
    battery_log_tag = log_tag;
}

// Getter functions
int get_battery_adc_unit_id() {
    return battery_adc_unit_id;
}

int get_battery_adc_ulp_mode() {
    return battery_adc_ulp_mode;
}

int get_battery_adc_bitwidth() {
    return battery_adc_bitwidth;
}

int get_battery_adc_atten() {
    return battery_adc_atten;
}

int get_battery_adc_channel() {
    return battery_adc_channel;
}

int get_battery_max_voltage() {
    return battery_max_voltage;
}

int get_battery_min_voltage() {
    return battery_min_voltage;
}

int get_battery_voltage_multiplier() {
    return battery_voltage_multiplier;
}

const char* get_battery_log_tag() {
    return battery_log_tag;
}

static bool example_adc_calibration_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle) {
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI("BATTERY", "Calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI("BATTERY", "Calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
                .unit_id = unit,
                .atten = atten,
                .bitwidth = BATTERY_ADC_BITWIDTH,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI("BATTERY", "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW("BATTERY", "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE("BATTERY", "Invalid arg or no memory");
    }

    return calibrated;
}

void init_adc_calibration(void) {
    // ADC1 INIT
    adc_oneshot_unit_init_cfg_t init_config1 = {
            .unit_id = battery_adc_unit_id,
            .ulp_mode = battery_adc_ulp_mode,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    // ADC 1 CONFIG
    adc_oneshot_chan_cfg_t config = {
            .bitwidth = battery_adc_bitwidth,
            .atten = battery_adc_atten,
    };

    // Configure the ADC channel and check for errors
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, battery_adc_channel, &config));

    // ADC 1 Calibration init
    example_adc_calibration_init(battery_adc_unit_id, battery_adc_channel, battery_adc_atten, &adc_cali_handle);
}

uint32_t read_battery_voltage(void) {
    int raw = 0;
    int voltage = 0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, battery_adc_channel, &raw));
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_handle, raw, &voltage));
    // Battery via voltage divider 1M Ohm to 1M Ohm -> Voltage * 2
    return voltage * battery_voltage_multiplier;
}

uint8_t calc_battery_percentage(uint32_t battery_voltage) {
    if (battery_voltage >= battery_max_voltage) {
        return 100;
    } else if (battery_voltage <= battery_min_voltage) {
        return 0;
    } else {
        uint32_t current_diff_voltage = battery_voltage - battery_min_voltage;
        return current_diff_voltage / (BATTERY_PERCENTAGE_FACTOR / 100);
    }
}
