/**
 * @file ESP32_Wifi_custom.h
 * @brief Header file for custom WiFi operations on the ESP32.
 *
 * This file contains the default configurations, variable declarations, and function prototypes
 * for custom WiFi operations using the ESP32 platform.
 */

#ifndef ESP_TEST_MANUELL_CUSTOM_WIFI_H
#define ESP_TEST_MANUELL_CUSTOM_WIFI_H

#include <string.h>
#include "esp_event.h"
#include "esp_wifi.h"

// Default WiFi Configuration
#define WIFI_SSID           "MyWIFI"              ///< Default SSID
#define WIFI_PASS           "baumannDo1995"       ///< Default Password
#define WIFI_MAX_RETRY      10                    ///< Default maximum retry attempts
#define WIFI_TAG            "WIFI"

// Setter, Getter for Configuration

/**
 * @brief Set the WiFi SSID.
 *
 * @param ssid New SSID for WiFi connection.
 */
void set_wifi_ssid(const char* ssid);

/**
 * @brief Set the WiFi password.
 *
 * @param password New password for WiFi connection.
 */
void set_wifi_pass(const char* password);

/**
 * @brief Set the maximum number of retries for connecting to WiFi.
 *
 * @param max_retry New maximum retry attempts.
 */
void set_wifi_maximum_retry(int max_retry);

/**
 * @brief Set the log tag for Wifi operations.
 * @param log_tag Log tag string.
 */
void set_wifi_log_tag(const char* log_tag);

/**
 * @brief Get the WiFi SSID.
 *
 * @return Current SSID.
 */
const char* get_wifi_ssid(void);

/**
 * @brief Get the WiFi password.
 *
 * @return Current password.
 */
const char* get_wifi_pass(void);

/**
 * @brief Get the maximum number of retries for connecting to WiFi.
 *
 * @return Current maximum retry attempts.
 */
int get_wifi_maximum_retry(void);

/**
 * @brief Get the log tag for Wifi operations.
 * @return Log tag string.
 */
const char* get_wifi_log_tag();

// Functions

/**
 * @brief WiFi event handler.
 *
 * @param arg User argument passed to the handler
 * @param event_base Base ID of the event
 * @param event_id ID of the event
 * @param event_data Data associated with the event
 */
void event_handler(void* arg, esp_event_base_t event_base,
                   int32_t event_id, void* event_data);

/**
 * @brief Initialize WiFi in station mode.
 */
void wifi_init_sta(void);

#endif //ESP_TEST_MANUELL_CUSTOM_WIFI_H
