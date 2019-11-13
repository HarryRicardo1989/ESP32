/**
 * @file MCPWMOperator.hpp
 * @author Taivison Martins Leite (tavison@grupocriar)
 * @brief Define a classe para Manipular o MCPWMOperator do ESP32
 * @version 0.1
 * @date 2019-10-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _MCPWM_OPERATOR_H_
#define _MCPWM_OPERATOR_H_

#include <driver/mcpwm.h>
#include <soc/mcpwm_struct.h>

namespace Perifericos
{
#define GPIO_NOT_USED -1

class MCPWMOperator
{
private:
    mcpwm_unit_t unit;
    mcpwm_timer_t timer;
    mcpwm_duty_type_t duty_type;

public:
    /**
     * @brief Construct a new MCPWMOperator object
     * 
     * @param unit Seleciona a Unidade 0 ou 1
     * @param timer Seleciona o Timer 0 - 2
     * @param gpio_pwm_A O pino qual será usado para a saída A, use valor negativo ou acima de 40 para não configurar
     * @param gpio_pwm_B O pino qual será usado para a saída A, use valor negativo ou acima de 40 para não configurar
     * @param config Estrutura de Configuração para o Operador
     */
    MCPWMOperator(mcpwm_unit_t unit, mcpwm_timer_t timer, int gpio_pwm_A, int gpio_pwm_B, mcpwm_config_t *config);

    /**
     * @brief Retorna a Frequencia configurada para o operador
     * 
     * @return uint32_t 
     */
    uint32_t GetFrequency(void);

    /**
     * @brief Ajusta a Frequência em Hz.
     * 
     * @param frequencia em Hz
     */
    void SetFrequency(uint32_t frequencia);

    /**
     * @brief Ajusta o Duty Cycle para a saída A deste Modulo Operador.
     * 
     * @param duty O valor do duty cycle expresso em Microssegundos.
     */
    void SetDutyMicroSecondsPWM_A(uint32_t duty);
    /**
     * @brief Ajusta o Duty Cycle para a saída B deste Modulo Operador.
     * 
     * @param duty O valor do duty cycle expresso em Microssegundos.
     */
    void SetDutyMicroSecondsPWM_B(uint32_t duty);

    /**
     * @brief Ajusta o Duty Cycle para a saída A deste Modulo Operador
     * 
     * @param duty O valor do duty cycle em expresso em porcentagem.
     */
    void SetDutyPWM_A(float duty);

    /**
     * @brief Ajusta o Duty Cycle para a saída B deste Modulo Operador
     * 
     * @param duty O valor do duty cycle em expresso em porcentagem.
     */
    void SetDutyPWM_B(float duty);

    /**
     * @brief Obtém o valor do duty da saída A
     * 
     * @return float O valor do duty em porcentagem
     */
    inline float GetDutyPWM_A(void)
    {
        return mcpwm_get_duty(unit, timer, MCPWM_OPR_A);
    }

    /**
     * @brief Obtém o valor do duty da saída B
     * 
     * @return float O valor do duty em porcentagem
     */
    inline float GetDutyPWM_B(void)
    {
        return mcpwm_get_duty(unit, timer, MCPWM_OPR_B);
    }

    /**
     * @brief Para o PWM na saída A
     * 
     */
    inline void Stop_A(void)
    {
        mcpwm_set_signal_low(unit, timer, MCPWM_OPR_A);
    }

    /**
     * @brief Aciona 0% do duty na saída B
     * 
     */
    inline void Stop_B(void)
    {
        mcpwm_set_signal_low(unit, timer, MCPWM_OPR_B);
    }

    /**
     * @brief Inicia o sinal PWM na saída A
     * 
     */
    inline void Start_A(void)
    {
        mcpwm_set_duty_type(unit, timer, MCPWM_OPR_A, duty_type);
    }

    /**
     * @brief Reinicia o PWM na saída B
     * 
     */
    inline void Start_B(void)
    {
        mcpwm_set_duty_type(unit, timer, MCPWM_OPR_B, duty_type);
    }
};
} // namespace Perifericos
#endif // _MCPWM_OPERATOR_H_