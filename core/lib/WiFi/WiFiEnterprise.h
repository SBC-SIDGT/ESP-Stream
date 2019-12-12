#ifndef WiFiEnterprise_h
#define WiFiEnterprise_h

#include <Arduino.h>
#include <esp_wpa2.h>
#include <WiFi.h>

#define SSID "eduroam"
#define EAP_ANONYMOUS "anonymous@upm.es"
#define EAP_USERNAME "javier.asilva@alumnos.upm.es"
#define EAP_PASSWORD "JaVi91Cuchi98_/"

class WiFiEnterprise {
    public:
        WiFiEnterprise(void);
        void setup(bool block=true, bool restart=true);
        void loop(bool block=true, bool restart=true);
    private:
        esp_wpa2_config_t config;
};

#endif