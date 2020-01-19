#include "WiFiEnterprise.h"

WiFiEnterprise::WiFiEnterprise(void) {
    config = WPA2_CONFIG_INIT_DEFAULT();
}

void WiFiEnterprise::setup(bool block, bool restart) {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *) EAP_ANONYMOUS, strlen(EAP_ANONYMOUS));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *) EAP_USERNAME, strlen(EAP_USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *) EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wifi_sta_wpa2_ent_enable(&config);

    WiFi.begin(SSID);
    if (block) {
        uint8_t counter = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            counter++;
            if (counter == 60 && restart) {
                ESP.restart();
            }
        }
    }
}

void WiFiEnterprise::loop(bool block, bool restart) {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(SSID);
        if (block) {
            uint8_t counter = 0;
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                counter++;
                if (counter == 60 && restart) {
                    ESP.restart();
                }
            }
        }
    }
}
