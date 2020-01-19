#include <Arduino.h>
#include <camera_pins.h>
#include <ESPCamera.h>
#include <HTTPRequests.h>
#include <WiFiEnterprise.h>

ESPCamera *camera    = new ESPCamera();
WiFiEnterprise *wifi = new WiFiEnterprise();
HTTPRequest *request = new HTTPRequest(camera);

void setup() {
    Serial.begin(9600);
    Serial.setDebugOutput(true);
    Serial.println();

    wifi->setup();

    camera->setup();
    request->setup();

    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
}

void loop() {
    wifi->loop();
    request->loop();
}