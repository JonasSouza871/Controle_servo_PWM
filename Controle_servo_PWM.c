#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definições de parâmetros para o controle do servo
#define PERIODO_PWM_US 20000  // Período total do PWM: 20ms (50Hz)
#define PULSO_0_GRAUS 500     // Pulso para 0°: 500µs
#define PULSO_180_GRAUS 2400  // Pulso para 180°: 2400µs
#define PASSO_US 5            // Incremento/decremento de 5µs por pulso
#define ATRASO_MS 10          // Atraso de 10ms entre ajustes
#define PINO_SERVO 22         // Pino conectado ao servomotor

// Inicializa e configura o PWM no pino do servo
void configurar_pwm(uint pino) {
    gpio_set_function(pino, GPIO_FUNC_PWM); // Define a função do pino como PWM
    uint fatia_pwm = pwm_gpio_to_slice_num(pino); // Obtém a fatia de PWM correspondente ao pino
    
    pwm_set_clkdiv(fatia_pwm, 125.0f); // Define a frequência do PWM para 1MHz (1µs por contagem)
    pwm_set_wrap(fatia_pwm, PERIODO_PWM_US - 1); // Define o período total do PWM (20ms)
    pwm_set_enabled(fatia_pwm, true); // Ativa o PWM
}

// Define o pulso PWM para controlar a posição do servo
void definir_angulo_servo(uint pino, int pulso) {
    uint fatia_pwm = pwm_gpio_to_slice_num(pino);
    pwm_set_chan_level(fatia_pwm, PWM_CHAN_A, pulso);
}

int main() {
    stdio_init_all(); // Inicializa comunicação padrão
    configurar_pwm(PINO_SERVO); // Configura o PWM no pino do servo

    int pulso_atual = PULSO_0_GRAUS; // Começa com o servo na posição 0°
    int direcao_passo = PASSO_US; // Define a direção do movimento

    while (true) {
        definir_angulo_servo(PINO_SERVO, pulso_atual); // Ajusta o ângulo do servo
        sleep_ms(ATRASO_MS); // Aguarda um tempo para suavizar o movimento

        // Atualiza o pulso para movimentar o servo gradualmente
        pulso_atual += direcao_passo;

        // Inverte a direção do movimento ao atingir os limites
        if (pulso_atual >= PULSO_180_GRAUS) {
            pulso_atual = PULSO_180_GRAUS;
            direcao_passo = -PASSO_US;
        } else if (pulso_atual <= PULSO_0_GRAUS) {
            pulso_atual = PULSO_0_GRAUS;
            direcao_passo = PASSO_US;
        }
    }
    return 0;
}