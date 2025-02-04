# README - Atividade 1

## Descrição
Este projeto implementa um semáforo utilizando o microcontrolador Raspberry Pi Pico W e a função `add_repeating_timer_ms()` do Pico SDK. O sistema alterna os estados do semáforo a cada 3 segundos e exibe mensagens na porta serial a cada 1 segundo.

## Objetivo
Implementar um semáforo com temporização de 3 segundos para cada alteração de sinal, seguindo os requisitos descritos na atividade.

## Componentes Utilizados
1. **Microcontrolador:** Raspberry Pi Pico W
2. **LEDs:** 3 LEDs (Vermelho, Amarelo e Verde)
3. **Resistores:** 3 resistores de 330 Ω
4. **Ambiente de Simulação:** Wokwi e BitDogLab

## Requisitos
1. O semáforo deve iniciar com o LED vermelho ligado.
2. A cada 3 segundos, o estado do semáforo deve mudar na seguinte ordem: **Vermelho → Amarelo → Verde → Vermelho**.
3. A lógica de troca de estados deve ser implementada na função de callback do temporizador.
4. O loop principal deve imprimir uma mensagem na porta serial a cada 1 segundo.
5. Deve ser realizado um experimento no BitDogLab utilizando um LED RGB nos GPIOs 11, 12 e 13.

## Estrutura do Código
O código está organizado da seguinte forma:

- **Definição de estados**: Enum `traffic_light_state` para representar os estados do semáforo.
- **Configuração dos LEDs**: Os LEDs estão associados aos GPIOs 11, 12 e 13.
- **Callback do temporizador**: A função `repeating_timer_callback()` é chamada a cada 3 segundos para alternar os estados do semáforo.
- **Loop principal**: Imprime uma mensagem na serial a cada segundo.

## Como Executar
1. Configure o ambiente de desenvolvimento com o Pico SDK.
2. Compile e rode a simulação do wokwi através da extensão e com o arquivo diagram.json.
2. Opcionalmente, envie o código para o Raspberry Pi Pico W.
3. Observe a alternância dos LEDs a cada 3 segundos.
4. Monitore a porta serial para visualizar as mensagens enviadas a cada 1 segundo.

