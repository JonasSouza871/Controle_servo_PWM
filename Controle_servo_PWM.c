#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_PERIOD_US 20000    // Período total de 20ms (50Hz)
#define SERVO_180_DEG 2400     // 2400µs = 0,12 do período (180 graus)
#define SERVO_90_DEG 1470      // 1470µs = 0,0735 do período (90 graus)
#define SERVO_0_DEG 500        // 500µs = 0,025% do período (0 graus)
#define DELAY_MS 5000          // Tempo de espera entre posições
#define Pino_servo 22 //Pino que o servo estará conectado

int main() {
    stdio_init_all();
    gpio_set_function(Pino_servo, GPIO_FUNC_PWM); // seta o pino do servo como função PWM
    uint slice_num = pwm_gpio_to_slice_num(Pino_servo);
    pwm_set_clkdiv(slice_num, 125.0f);  // Clock = 1µs/incremento
    pwm_set_wrap(slice_num, PWM_PERIOD_US - 1);  // 19999 = 20ms
    pwm_set_enabled(slice_num, true); //controle das pociçoes

    // Posição 1: 180 graus -> 0,12 de dusty cicle
    pwm_set_chan_level(slice_num, PWM_CHAN_A, SERVO_180_DEG);
    sleep_ms(DELAY_MS);
    // Posição 2: 90 graus  -> 0,0735 de dusty cicle
    pwm_set_chan_level(slice_num, PWM_CHAN_A, SERVO_90_DEG);
    sleep_ms(DELAY_MS);
    // Posição 3: 0 graus -> 0,025 de dusty cycle
    pwm_set_chan_level(slice_num, PWM_CHAN_A, SERVO_0_DEG);
    sleep_ms(DELAY_MS);

    return 0;
}
