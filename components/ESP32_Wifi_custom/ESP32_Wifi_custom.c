#include "ESP32_Wifi_custom.h"
#include "esp_log.h"
#include "string.h"

// Global configuration variables
static char *wifi_ssid = WIFI_SSID;
static char *wifi_pass = WIFI_PASS;
static int wifi_maximum_retry = WIFI_MAX_RETRY;
static const char *wifi_log_tag = WIFI_TAG;

static int s_retry_num = 0;

void event_handler(void* arg, esp_event_base_t event_base,
                   int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < wifi_maximum_retry) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(WIFI_TAG, "retry to connect to the AP");
        } else {
            ESP_LOGI(WIFI_TAG, "connect to the AP fail");
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        s_retry_num = 0;
        ESP_LOGI(WIFI_TAG, "got ip");
    }
}

void wifi_init_sta(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
            .sta = {
                    .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                    .pmf_cfg = {
                            .capable = true,
                            .required = false
                    },
            },
    };

    strcpy((char *)wifi_config.sta.ssid, (char *) wifi_ssid);
    strcpy((char *)wifi_config.sta.password, (char *) wifi_pass);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(WIFI_TAG, "wifi_init_sta finished.");
}

void set_wifi_ssid(const char* ssid) {
    strncpy(wifi_ssid, ssid, sizeof(wifi_ssid) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0'; // Ensure null termination
}

void set_wifi_pass(const char* password) {
    strncpy(wifi_pass, password, sizeof(wifi_pass) - 1);
    wifi_pass[sizeof(wifi_pass) - 1] = '\0'; // Ensure null termination
}

void set_wifi_maximum_retry(int max_retry) {
    wifi_maximum_retry = max_retry;
}

void set_wifi_log_tag(const char* log_tag) {
    wifi_log_tag = log_tag;
}

const char* get_wifi_ssid(void) {
    return wifi_ssid;
}

const char* get_wifi_pass(void) {
    return wifi_pass;
}

int get_wifi_maximum_retry(void) {
    return wifi_maximum_retry;
}

const char* get_wifi_log_tag() {
    return wifi_log_tag;
}
