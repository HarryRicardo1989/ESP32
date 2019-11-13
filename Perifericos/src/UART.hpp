/**
 * @file UART.hpp
 * @author Taivison Martins Leite (taivison@grupocriar)
 * @brief Define a classe para Manipular as UART's  do ESP32
 * @version 0.1
 * @date 2019-10-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _UART_HPP_
#define _UART_HPP_

#include <driver/uart.h>
#include <string>
#include <vector>
#include <array>
#include <freertos/FreeRTOS.h>
#include "Queue.hpp"
#include <cstdarg>
#include <stdlib.h>

namespace Perifericos
{
typedef struct UART_PINS
{
    int tx_io_num;
    int rx_io_num;
    int rts_io_num;
    int cts_io_num;
} uart_pins_t;

typedef struct UART_DRIVER_OP
{
    int rx_buffer_size;
    int tx_buffer_size;
    int queue_size;
    int intr_alloc_flags;
} uart_driver_options_t;

class UART
{
private:
    uart_port_t port;
    RTOS::Queue<uart_event_t> *queue;
    int rx_buffer_size;
    int tx_buffer_size;

    inline int _read_bytes(uint8_t *buf, int numBytes, TickType_t ticks)
    {
        return uart_read_bytes(port, buf, numBytes, ticks);
    }

public:
    /**
     * @brief Construct a new UART object
     * 
     * @param port Porta a ser Utilizada
     * @param param Parametros Básicos de comunicação
     * @param pinos Pinos a serem utilizados, caso NULL usa os valores default
     * @param driver_opt Opçoes de Buffer e Interrupções
     */
    UART(uart_port_t port, uart_config_t *param, uart_pins_t *pinos, uart_driver_options_t *driver_opt);

    /**
     * @brief Retorna um array contendo os bytes recebidos
     * 
     * @param byteNum o número máximo de bytes para serem recebidos
     * @param ticks o numero de ticks do FreeRTOS para aguardar os bytes serem recebidos
     * @return std::vector<uint8_t> 
     */
    std::vector<uint8_t> ReadBytes(int byteNum, TickType_t ticks);

    /**
     * @brief Retorna um array contendo os bytes recebidos
     * 
     * @param ticks Número Máximo de Ticks para aguardar.
     * @return std::vector<uint8_t> 
     */
    inline std::vector<uint8_t> ReadBytes(TickType_t ticks) { return ReadBytes(rx_buffer_size, ticks); }
    /**
     * @brief Retorna a string Lida
     * 
     * @param bytenum 
     * @param ticks 
     * @return std::string 
     */
    std::string ReadString(int bytenum, TickType_t ticks);
    inline std::string ReadString(TickType_t ticks) { return ReadString(rx_buffer_size, ticks); }


    int WriteBytes(std::vector<uint8_t> &bytes);
    int WriteString(const std::string &str);
};
} // namespace Perifericos

#endif // _UART_HPP_
