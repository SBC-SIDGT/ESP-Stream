#include "ESPCamera.h"

ESPCamera::ESPCamera() {
    camera_config_t *config = new camera_config_t();
    _config = *config;
}

uint8_t ESPCamera::setup() {
    _config.ledc_channel = LEDC_CHANNEL_0;
    _config.ledc_timer = LEDC_TIMER_0;
    _config.pin_d0 = Y2_GPIO_NUM;
    _config.pin_d1 = Y3_GPIO_NUM;
    _config.pin_d2 = Y4_GPIO_NUM;
    _config.pin_d3 = Y5_GPIO_NUM;
    _config.pin_d4 = Y6_GPIO_NUM;
    _config.pin_d5 = Y7_GPIO_NUM;
    _config.pin_d6 = Y8_GPIO_NUM;
    _config.pin_d7 = Y9_GPIO_NUM;
    _config.pin_xclk = XCLK_GPIO_NUM;
    _config.pin_pclk = PCLK_GPIO_NUM;
    _config.pin_vsync = VSYNC_GPIO_NUM;
    _config.pin_href = HREF_GPIO_NUM;
    _config.pin_sscb_sda = SIOD_GPIO_NUM;
    _config.pin_sscb_scl = SIOC_GPIO_NUM;
    _config.pin_pwdn = PWDN_GPIO_NUM;
    _config.pin_reset = RESET_GPIO_NUM;
    _config.xclk_freq_hz = 20000000;
    _config.pixel_format = PIXFORMAT_JPEG;
    //init with high specs to pre-allocate larger buffers
    _config.frame_size = FRAMESIZE_UXGA;
    _config.jpeg_quality = 10;
    _config.fb_count = 2;
    esp_err_t err = esp_camera_init(&_config);
    return err != ESP_OK ? 1 : 0;
}

camera_fb_t* ESPCamera::takePicture() {
    camera_fb_t *pic = NULL;
    pic = esp_camera_fb_get();
    return !pic ? NULL : pic;
}

ESPCamera::~ESPCamera() {
    delete &_config;
}