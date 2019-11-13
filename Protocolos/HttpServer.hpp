/**
 * @file HttpServer.hpp
 * @author Taivison Martins Leite (taivison@grupocriar)
 * @brief Define a classe para Manipular o HTTP Server do ESP32
 * @version 0.1
 * @date 2019-10-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _HTTP_SERVER_HPP_
#define _HTTP_SERVER_HPP_

#include <http_server.h>
#include <esp_https_server.h>
#include <string>

namespace Protocols
{
class HttpServer
{
private:
    /* data */
    httpd_handle_t handle;
    bool ssl;
public:

    HttpServer(bool ssl = false, httpd_uri_match_func_t func = NULL, uint16_t port = 80);
    /**
     * @brief Configura a Uri e a função que devera ser invocada
     * 
     * @param uri o endereço 
     * @param method Método do Protocolo HTTP
     * @param handler Função que será invocada 
     * @param ctx parametro a ser passado para função invocada
     */
    void ConfigureUri(std::string &uri, httpd_method_t method,
                      esp_err_t (*handler)(httpd_req_t *r), void *ctx);
};
} // namespace Protocols
#endif // _HTTP_SERVER_HPP_