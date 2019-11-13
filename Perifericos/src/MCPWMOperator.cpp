#include "MCPWMOperator.hpp"

namespace Perifericos
{
MCPWMOperator::MCPWMOperator(mcpwm_unit_t unit, mcpwm_timer_t timer, int gpio_pwm_A,
                             int gpio_pwm_B, mcpwm_config_t *config)
{
    this->timer = timer;
    this->unit = unit;
    this->duty_type = config->duty_mode;
    mcpwm_io_signals_t pwm_a, pwm_b;
    switch (timer)
    {
    case MCPWM_TIMER_0:
        pwm_a = MCPWM0A;
        pwm_b = MCPWM0B;
        break;
    case MCPWM_TIMER_1:
        pwm_a = MCPWM1A;
        pwm_b = MCPWM1B;
        break;
    case MCPWM_TIMER_2:
        pwm_a = MCPWM2A;
        pwm_b = MCPWM2B;
        break;
    default:
        return;
    }
    if (gpio_pwm_A < 40 && gpio_pwm_A >= 0)
        mcpwm_gpio_init(unit, pwm_a, gpio_pwm_A);
    if (gpio_pwm_B < 40 && gpio_pwm_B >= 0)
        mcpwm_gpio_init(unit, pwm_b, gpio_pwm_B);
    mcpwm_init(unit, timer, config);
}

void MCPWMOperator::SetFrequency(uint32_t frequencia)
{
    mcpwm_set_frequency(unit, timer, frequencia);
}

uint32_t MCPWMOperator::GetFrequency(void)
{
    return mcpwm_get_frequency(unit, timer);
}

void MCPWMOperator::SetDutyMicroSecondsPWM_A(uint32_t duty)
{
    mcpwm_set_duty_in_us(unit, timer, MCPWM_OPR_A, duty);
}

void MCPWMOperator::SetDutyMicroSecondsPWM_B(uint32_t duty)
{
    mcpwm_set_duty_in_us(unit, timer, MCPWM_OPR_B, duty);
}

void MCPWMOperator::SetDutyPWM_A(float duty)
{
    mcpwm_set_duty(unit, timer, MCPWM_OPR_A, duty);
}

void MCPWMOperator::SetDutyPWM_B(float duty)
{
    mcpwm_set_duty(unit, timer, MCPWM_OPR_B, duty);
}

} // namespace Perifericos
