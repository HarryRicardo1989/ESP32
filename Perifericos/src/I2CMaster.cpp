#include "I2CMaster.hpp"

namespace Perifericos
{
I2CMaster::I2CMaster(i2c_port_t port, i2c_gpio_config_t *gpio_config, uint32_t clk)
{
    this->port = port;
    i2c_config_t config;
    config.mode = I2C_MODE_MASTER;
    config.scl_io_num = gpio_config->scl;
    config.sda_io_num = gpio_config->sda;
    config.sda_pullup_en = gpio_config->sda_pullup;
    config.scl_pullup_en = gpio_config->scl_pullup;
    config.master.clk_speed = clk;
    i2c_param_config(port, &config);
    i2c_driver_install(port, I2C_MODE_MASTER, 0, 0, 0);
}

void I2CMaster::WriteBytes(uint8_t slave_addr, const std::vector<uint8_t> &buffer, TickType_t ticks)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr << 1) | I2C_MASTER_WRITE, true);
    size_t size = buffer.size();
    size_t offset = 0;
    while ((size_t)(size / 32) > 0)
    {
        i2c_master_write(cmd, (uint8_t *)(&buffer.at(offset)), 32, true);
        size -= 32;
        offset += 32;
    }
    if (size > 0)
        i2c_master_write(cmd, (uint8_t *)(&buffer.at(offset)), size, true);
    i2c_master_stop(cmd);
    ESP_ERROR_CHECK(i2c_master_cmd_begin(port, cmd, ticks));
    i2c_cmd_link_delete(cmd);
}

std::vector<uint8_t> I2CMaster::ReadBytes(uint8_t slave_addr, size_t size, TickType_t ticks)
{
    std::vector<uint8_t> buffer(size);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, buffer.data(), size, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    int status = i2c_master_cmd_begin(port, cmd, ticks);
    i2c_cmd_link_delete(cmd);
    if (status != ESP_OK)
        return {};
    return buffer;
}

} // namespace Perifericos
