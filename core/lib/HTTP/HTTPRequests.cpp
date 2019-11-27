#include "HTTPRequests.h"

HTTPServer::HTTPServer() {
    _camera_handler = NULL;
    _config = HTTPD_DEFAULT_CONFIG();
    _camera = nullptr;
}

uint8_t HTTPServer::setup(ESPCamera *camera) {
    HTTPServer::_camera = camera;

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
    HTTPServer::_camera->~ESPCamera();
    _camera_handler = NULL;
}