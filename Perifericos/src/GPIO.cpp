#include "GPIO.hpp"
namespace Perifericos
{


bool GPIO::isr_is_installed = false;

GPIO::GPIO(gpio_num_t num, gpio_mode_t mode)
{
    gpio_num = num;
    gpio_set_direction(num, mode);
}

GPIO::GPIO(gpio_num_t num, gpio_mode_t mode, gpio_pull_mode_t pull_mode)
{
    gpio_num = num;
    gpio_set_direction(num, mode);
    gpio_set_pull_mode(num, pull_mode);
}

GPIO::GPIO(gpio_num_t num, gpio_mode_t mode, gpio_pull_mode_t pull_mode, gpio_int_type_t int_mode, gpio_isr_t handle, void *pArgs)
{
    gpio_num = num;
    gpio_set_direction(num, mode);
    gpio_set_pull_mode(num, pull_mode);
    gpio_set_intr_type(num,int_mode);
    if (!isr_is_installed)
    {
        gpio_install_isr_service(0);
        isr_is_installed = true;
    }
    gpio_isr_handler_add(num, handle, pArgs);
}
} // namespace Libraries