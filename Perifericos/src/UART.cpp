#include "UART.hpp"

namespace Perifericos
{
UART::UART(uart_port_t port, uart_config_t *param, uart_pins_t *pinos, uart_driver_options_t *driver_opt)
{
    this->port = port;
    uart_param_config(port, param);
    if (pinos != nullptr)
        uart_set_pin(port, pinos->tx_io_num, pinos->rx_io_num, pinos->rts_io_num, pinos->cts_io_num);
    else
        uart_set_pin(port, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    QueueHandle_t *handle = NULL;
    queue = nullptr;
    if (driver_opt->queue_size > 0)
        handle = (QueueHandle_t *)malloc(sizeof(QueueHandle_t));
    else
        handle = NULL;
    ESP_ERROR_CHECK(uart_driver_install(port, driver_opt->rx_buffer_size, driver_opt->rx_buffer_size,
                        driver_opt->queue_size, handle, driver_opt->intr_alloc_flags));
    rx_buffer_size = driver_opt->rx_buffer_size;
    tx_buffer_size = driver_opt->tx_buffer_size;
    if (handle != NULL)
        queue = new RTOS::Queue<uart_event_t>(handle);
}

std::vector<uint8_t> UART::ReadBytes(int byteNum, TickType_t ticks)
{
    std::vector<uint8_t> buffer(byteNum);
    int total = _read_bytes(buffer.data(), byteNum, ticks);
    if (total > 0)
    {
        if (total != buffer.size())
            buffer.resize(total);
        return buffer;
    }
    else
        return {};
}

std::string UART::ReadString(int byteNum, TickType_t ticks)
{
    std::string buffer(byteNum + 1, '\0');
    int total = _read_bytes((uint8_t *)buffer.data(), byteNum, ticks);
    if (total > 0)
    {
        if (total != buffer.size())
            buffer.resize(total);
        return buffer;
    }
    else
        return "";
}

int UART::WriteBytes(std::vector<uint8_t> &bytes)
{
    return uart_write_bytes(port, (const char *)bytes.data(), bytes.size());
}

int UART::WriteString(const std::string &str)
{
    return uart_write_bytes(port, str.c_str(), str.size());
}

} // namespace Perifericos