#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PERIODO_PWM_US   20000   // Período de 20ms (50Hz)
#define SERVO_180_GRAUS  2400    // 180° - 2400µs (0.12)
#define SERVO_90_GRAUS   1470    // 90° - 1470µs (0.0735)
#define SERVO_0_GRAUS    500     // 0° - 500µs (0.025)
#define ATRASO_MS        5000    // Espera entre posições (5s)
#define PASSO_US         5       // Incremento de pulso para movimento suave
#define ATRASO_PASSO_MS  10      // Espera entre ajustes
#define PINO_SERVO       22      // Pino do servo

int main() {
    stdio_init_all();

    // Configura PWM
    gpio_set_function(PINO_SERVO, GPIO_FUNC_PWM);
    uint num_slice = pwm_gpio_to_slice_num(PINO_SERVO);

    // Ajustes do PWM (1MHz = 125MHz/125)
    pwm_set_clkdiv(num_slice, 125.0f);
    pwm_set_wrap(num_slice, PERIODO_PWM_US - 1);
    pwm_set_enabled(num_slice, true);

    // Posições fixas
    pwm_set_chan_level(num_slice, PWM_CHAN_A, SERVO_180_GRAUS);
    sleep_ms(ATRASO_MS);
    
    pwm_set_chan_level(num_slice, PWM_CHAN_A, SERVO_90_GRAUS);
    sleep_ms(ATRASO_MS);
    
    pwm_set_chan_level(num_slice, PWM_CHAN_A, SERVO_0_GRAUS);
    sleep_ms(ATRASO_MS);

    // Movimento contínuo
    int pulso_atual = SERVO_0_GRAUS;
    int passo = PASSO_US;

    while (true) {
        pwm_set_chan_level(num_slice, PWM_CHAN_A, pulso_atual);
        sleep_ms(ATRASO_PASSO_MS);

        pulso_atual += passo;
        
        // Inverte direção nos limites
        if (pulso_atual >= SERVO_180_GRAUS) {
            pulso_atual = SERVO_180_GRAUS;
            passo = -PASSO_US;
        } 
        else if (pulso_atual <= SERVO_0_GRAUS) {
            pulso_atual = SERVO_0_GRAUS;
            passo = PASSO_US;
        }
    }

    return 0;
}