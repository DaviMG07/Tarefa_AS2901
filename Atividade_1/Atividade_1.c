#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"    // Necessário para a função add_repeating_timer_ms()

// Enumeração para os estados do semáforo
typedef enum {
    RED,
    YELLOW,
    GREEN
} traffic_light_state;

// Estado atual do semáforo (inicia em vermelho)
volatile traffic_light_state current_state = RED;

// Definição dos pinos dos LEDs (usados no BitDogLab)
const uint LED_RED    = 11;   // LED Vermelho
const uint LED_YELLOW = 12;   // LED Amarelo
const uint LED_GREEN  = 13;   // LED Verde

/**
 * @brief Função de callback do temporizador periódico.
 * 
 * Esta função é chamada a cada 3.000ms e realiza a troca de estado do semáforo:
 * - Se estiver em vermelho, desliga o LED vermelho, liga o LED amarelo e passa para o estado amarelo.
 * - Se estiver em amarelo, desliga o LED amarelo, liga o LED verde e passa para o estado verde.
 * - Se estiver em verde, desliga o LED verde, liga o LED vermelho e reinicia o ciclo.
 * 
 * @param t Ponteiro para a estrutura do timer (não utilizada neste exemplo).
 * @return true para manter o timer repetindo.
 */
bool repeating_timer_callback(struct repeating_timer *t) {
    switch(current_state) {
        case RED:
            gpio_put(LED_RED, false);
            gpio_put(LED_YELLOW, true);
            current_state = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_YELLOW, false);
            gpio_put(LED_GREEN, true);
            current_state = GREEN;
            break;
        case GREEN:
            gpio_put(LED_GREEN, false);
            gpio_put(LED_RED, true);
            current_state = RED;
            break;
        default:
            break;
    }
    return true; // Retorna true para continuar a repetição do timer
}

int main() {
    // Inicializa a comunicação serial e os pinos
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Estado inicial: LED vermelho ligado, os outros desligados
    gpio_put(LED_RED, true);
    gpio_put(LED_YELLOW, false);
    gpio_put(LED_GREEN, false);

    // Configura o timer para chamar a função de callback a cada 3000ms (3 segundos)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal: imprime uma mensagem a cada 1 segundo (1000ms)
    uint32_t seconds = 0;
    while (true) {
        printf("Tempo decorrido: %d s\n", seconds);
        sleep_ms(1000);
        seconds++;
    }

    return 0;
}
