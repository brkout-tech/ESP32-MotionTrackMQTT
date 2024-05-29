//
// Created by domin on 26.04.2024.
//

#include "ESP32_Mqtt_custom.h"

#include "esp_log.h"
#include "cJSON.h"


// Variables for MQTT Configuration
const char* mqtt_broker = MQTT_BROKER;               ///< MQTT broker URI
const char* mqtt_username = MQTT_USERNAME;           ///< MQTT username
const char* mqtt_password = MQTT_PASSWORD;           ///< MQTT password
const char* mqtt_log_tag = MQTT_TAG;                 ///< Tag for ESP logging

// Setter functions

void set_mqtt_broker(const char* broker) {
    mqtt_broker = broker;
}

void set_mqtt_username(const char* username) {
    mqtt_username = username;
}

void set_mqtt_password(const char* password) {
    mqtt_password = password;
}

void set_mqtt_log_tag(const char* log_tag) {
    mqtt_log_tag = log_tag;
}

// Getter functions

const char* get_mqtt_broker() {
    return mqtt_broker;
}

const char* get_mqtt_username() {
    return mqtt_username;
}

const char* get_mqtt_password() {
    return mqtt_password;
}

const char* get_mqtt_log_tag() {
    return mqtt_log_tag;
}

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD("MQTT", "Event dispatched from event loop base=%s, event_id=%ld", base, (long)event_id);
}

esp_mqtt_client_handle_t mqtt_app_start(void) {
    esp_mqtt_client_config_t mqtt_cfg = {
            .broker.address.uri = MQTT_BROKER,
            .credentials.username = MQTT_USERNAME,
            .credentials.authentication.password = MQTT_PASSWORD,
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
    return client;
}

void send_sensor_discovery(esp_mqtt_client_handle_t client, const sensor_config_t *config) {
    cJSON *root = cJSON_CreateObject();
    if(strcmp(config->device_class, "None") != 0) {
        cJSON_AddStringToObject(root, "device_class", config->device_class);
    }
    cJSON_AddStringToObject(root, "state_topic", config->state_topic);
    cJSON_AddStringToObject(root, "unit_of_measurement", config->unit_of_measurement);
    cJSON_AddStringToObject(root, "value_template", config->value_template);
    cJSON_AddStringToObject(root, "unique_id", config->unique_id);

    cJSON *device = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "device", device);
    cJSON_AddItemToObject(device, "identifiers", cJSON_CreateStringArray(&config->identifiers, 1));
    cJSON_AddStringToObject(device, "name", config->name);
    cJSON_AddStringToObject(device, "manufacturer", config->manufacturer);
    cJSON_AddStringToObject(device, "model", config->model);

    char *message = cJSON_Print(root);
    char topic[256];
    snprintf(topic, 256, "homeassistant/sensor/%s/%s/config", config->identifiers, config->sensor_type);

    esp_mqtt_client_publish(client, topic, message, 0, 1, 0);
    ESP_LOGI("MQTT", "Sent discovery message: %s", message);

    cJSON_Delete(root);
    free(message);
}

void send_all_sensor_discoveries(esp_mqtt_client_handle_t client, const sensor_config_t *sensor_configs, int number_of_configs) {
    for (int i = 0; i < number_of_configs; i++) {
        const sensor_config_t *config = &sensor_configs[i];
        send_sensor_discovery(client, config);
    }
}

void send_sensor_data_array(esp_mqtt_client_handle_t client, const sensor_data_t *sensor_data_array, size_t data_count) {
    char json_string[256]; // Stellen Sie sicher, dass dieser Puffer groß genug ist.
    cJSON *root;

    for (int i = 0; i < data_count; i++) {
        const sensor_data_t *data = &sensor_data_array[i];
        root = cJSON_CreateObject();

        switch (data->value.type) {
            case VALUE_TYPE_FLOAT:
                // Formatierung hier direkt im cJSON-Objekt
                snprintf(json_string, sizeof(json_string), "%.2f", data->value.float_value);
                cJSON_AddStringToObject(root, data->sensor_type, json_string);
                break;
            case VALUE_TYPE_INT:
                cJSON_AddNumberToObject(root, data->sensor_type, data->value.int_value);
                break;
            case VALUE_TYPE_DOUBLE:
                // Formatierung hier direkt im cJSON-Objekt
                snprintf(json_string, sizeof(json_string), "%.2f", data->value.double_value);
                cJSON_AddStringToObject(root, data->sensor_type, json_string);
                break;
            case VALUE_TYPE_STRING:
                cJSON_AddStringToObject(root, data->sensor_type, data->value.string_value);
                break;
        }

        char *formatted_json = cJSON_PrintUnformatted(root);
        esp_mqtt_client_publish(client, data->topic, formatted_json, 0, 1, 0);
        free(formatted_json);
        cJSON_Delete(root);
    }
}

