#include "HttpServer.hpp"

namespace Protocols
{
HttpServer::HttpServer(bool ssl = false, httpd_uri_match_func_t func = NULL, uint16_t port = 80)
{
    if (!ssl)
    {
        httpd_config_t config = HTTPD_DEFAULT_CONFIG();
        config.server_port = port;
        config.uri_match_fn = func;
        ESP_ERROR_CHECK(httpd_start(&handle,&config));
    }
    else
    {
        abort();
    }
    this->ssl = ssl;
}

void HttpServer::ConfigureUri(std::string &uri, httpd_method_t method,
                      esp_err_t (*handler)(httpd_req_t *r), void *ctx)
{
    httpd_uri_t uri_conf;
    uri_conf.handler = handler;
    uri_conf.method = method;
    uri_conf.uri = uri.c_str;
    uri_conf.user_ctx = ctx;
    ESP_ERROR_CHECK(httpd_register_uri_handler(handle,&uri_conf));
}

} // namespace Protocols
