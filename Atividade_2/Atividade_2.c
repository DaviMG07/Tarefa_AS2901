#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

/* Definição dos pinos para o LED RGB e o botão */
#define LED_BLUE      11
#define LED_RED       12
#define LED_GREEN     13
#define BUTTON        5

/* Tempo de atraso entre as mudanças de estado em milissegundos */
#define DELAY_MS      3000

/* Variáveis globais para controle da sequência e debounce */
volatile bool sequence_active = false;
volatile uint32_t last_press = 0;  /* Timestamp para debounce */

/* Protótipos das funções de callback */
int64_t callback_stage1(alarm_id_t id, void *user_data);
int64_t callback_stage2(alarm_id_t id, void *user_data);
int64_t callback_stage3(alarm_id_t id, void *user_data);

/* Função de callback para a 1ª etapa: desliga o LED azul */
int64_t callback_stage1(alarm_id_t id, void *user_data) {
    /* Desliga o LED azul e agenda a próxima etapa após DELAY_MS milissegundos */
    gpio_put(LED_BLUE, 0);
    add_alarm_in_ms(DELAY_MS, callback_stage2, NULL, true);
    return 0;
}

/* Função de callback para a 2ª etapa: desliga o LED vermelho */
int64_t callback_stage2(alarm_id_t id, void *user_data) {
    /* Desliga o LED vermelho e agenda a próxima etapa após DELAY_MS milissegundos */
    gpio_put(LED_RED, 0);
    add_alarm_in_ms(DELAY_MS, callback_stage3, NULL, true);
    return 0;
}

/* Função de callback para a 3ª etapa: desliga o LED verde */
int64_t callback_stage3(alarm_id_t id, void *user_data) {
    /* Desliga o LED verde e finaliza a sequência permitindo nova ativação */
    gpio_put(LED_GREEN, 0);
    sequence_active = false;
    return 0;
}

/* Função de tratamento de interrupção para o botão (com debounce simples) */
void button_callback(uint gpio, uint32_t events) {
    /* Implementa debounce: ignora se o intervalo entre pressões for menor que 200 ms */
    uint32_t now = to_ms_since_boot(get_absolute_time());
    if ((now - last_press) < 200)
        return;

    /* Se a sequência já está ativa, ignora o acionamento */
    if (sequence_active)
        return;

    last_press = now;

    /* Aciona a sequência: liga os LEDs e agenda a primeira etapa */
    sequence_active = true;
    gpio_put(LED_BLUE, 1);
    gpio_put(LED_RED, 1);
    gpio_put(LED_GREEN, 1);
    add_alarm_in_ms(DELAY_MS, callback_stage1, NULL, true);
}

/* Função setup para configurar os pinos GPIO */
void setup() {
    /* Inicializa o sistema de entrada/saída padrão */
    stdio_init_all();

    /* Configura os pinos dos LEDs como saída */
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    /* Configura o pino do botão como entrada com pull-up */
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    /* Configura a interrupção para o botão na borda de descida (falling edge) */
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);
}

int main() {
    setup();
    while (true) {
        tight_loop_contents();
    }
    return 0;
}
