#include "HTTPRequests.h"

HTTPServer::HTTPServer() {
    _camera_handler = NULL;
    _config = HTTPD_DEFAULT_CONFIG();
}

uint8_t HTTPServer::setup(void) {

    httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = &HTTPServer::handler,
        .user_ctx = NULL
    };
    if (httpd_start(&_camera_handler, &_config) == ESP_OK) {
        httpd_register_uri_handler(_camera_handler, &index_uri);
        return 1;
    }
    return 0;
}

HTTPServer::~HTTPServer() {
    camera_ptr->~ESPCamera();
    _camera_handler = NULL;
}


HTTPRequest::HTTPRequest(ESPCamera *camera) {
    _camera = camera;
}

void HTTPRequest::setup(void) {
    esp_http_client_config_t config = {0};
    config.url = URL;
    config.port = 80;
    config.timeout_ms = 500;
    config.method = HTTP_METHOD_POST;
    http_client = esp_http_client_init(&config);
}

void HTTPRequest::loop(void) {
    camera_fb_t *fb = _camera->takePicture();
    if (!fb) {
        return;
    }
    esp_http_client_set_post_field(http_client, (const char *)fb->buf, fb->len);

    esp_http_client_set_header(http_client, "Content-Type", "image/jpg"); // sending a jpg file

    esp_err_t err = esp_http_client_perform(http_client);
    if (err == ESP_OK) {
        Serial.print("esp_http_client_get_status_code: ");
        Serial.println(esp_http_client_get_status_code(http_client));
    }
    _camera->return_fb(fb);
}

HTTPRequest::~HTTPRequest(void) {
    esp_http_client_cleanup(http_client);
    delete &http_client;
    _camera->~ESPCamera();
}
