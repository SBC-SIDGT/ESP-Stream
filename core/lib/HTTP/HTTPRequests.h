#ifndef HTTPRequests_h
#define HTTPRequests_h

#include "esp_http_server.h"
#include "fb_gfx.h"

#include "ESPCamera.h"

typedef struct
{
    httpd_req_t *req;
    size_t len;
} jpg_chunking_t;

static size_t jpg_encode_stream(void *arg, size_t index, const void *data, size_t len)
{
    jpg_chunking_t *j = (jpg_chunking_t *)arg;
    if (!index)
    {
        j->len = 0;
    }
    if (httpd_resp_send_chunk(j->req, (const char *)data, len) != ESP_OK)
    {
        return 0;
    }
    j->len += len;
    return len;
}

class HTTPServer {
    public:
        HTTPServer();
        uint8_t setup(ESPCamera *camera);
        static esp_err_t handler(httpd_req_t *req) {
            esp_err_t res = ESP_OK;
            camera_fb_t *fb = HTTPServer::_camera->takePicture();
            if (!fb) {
                return ESP_FAIL;
            }
            httpd_resp_set_type(req, "image/jpeg");
            httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
            httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
            if (fb->format == PIXFORMAT_JPEG) {
                res = httpd_resp_send(req, (const char *)fb->buf, fb->len);
            } else {
                jpg_chunking_t jchunk = {req, 0};
                res = frame2jpg_cb(fb, 80, jpg_encode_stream, &jchunk) ? ESP_OK : ESP_FAIL;
                httpd_resp_send_chunk(req, NULL, 0);
            }
            HTTPServer::_camera->return_fb(fb);
            return res;
        }
        ~HTTPServer();
    private:
        httpd_config_t    _config;
        httpd_handle_t    _camera_handler;
        static ESPCamera *_camera;
};

#endif