/**
 * @file I2CMaster.hpp
 * @author Taivison Martins Leite (taivison@grupocriar)
 * @brief Define a Classe para Manipular a I2C do ESP32
 * @version 0.1
 * @date 2019-10-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _I2C_MASTER_HPP_
#define _I2C_MASTER_HPP_
#include <driver/i2c.h>
#include <vector>

namespace Perifericos
{

enum I2CError
{
    Sucesso,
    Fail,
    BusOcupada,
};

typedef struct I2CMasterConfigPins
{
    gpio_num_t sda;
    gpio_num_t scl;
    gpio_pullup_t sda_pullup;
    gpio_pullup_t scl_pullup;
} i2c_gpio_config_t;

class I2CMaster
{
private:
    i2c_port_t port;
public:
    /**
     * @brief Construct a new I2CMaster object
     * 
     * @param port 
     * @param gpio_config 
     * @param clk 
     */
    I2CMaster(i2c_port_t port, i2c_gpio_config_t *gpio_config, uint32_t clk);
    /**
     * @brief Envia os Bytes para o End solicitado
     * 
     * @param slave_addr Endereco de 7 bits
     * @param buffer Buffer contendo os bytes a serem enviados
     * @param ticks Tempo Máximo para aguardar o envio
     */
    void WriteBytes(uint8_t slave_addr,const std::vector<uint8_t> &buffer, TickType_t ticks);
    /**
     * @brief Recebe os Bytes do Endereco solicitado
     * 
     * @param slave_addr Endereco de 7 bits
     * @param size Tamanho do pacote a ser recebido
     * @param ticks Tempo Máximo para aguardar envio
     * @return std::vector<uint8_t> Buffer contendo os valores recebidos
     */
    std::vector<uint8_t> ReadBytes(uint8_t slave_addr, size_t size, TickType_t ticks);
};
} // namespace Perifericos
#endif // _I2C_MASTER_HPP_