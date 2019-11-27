#ifndef ESPCamera_h
#define ESPCamera_h

#include "esp_camera.h"
#include "camera_pins.h"

class ESPCamera
{
    public:
        ESPCamera();
        uint8_t setup();
        camera_fb_t *takePicture();
        void return_fb(camera_fb_t *fb);
        ~ESPCamera();
    private:
        camera_config_t _config;
};

#endif