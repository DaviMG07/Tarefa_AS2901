# README - Atividade 2

## Descrição
Este projeto implementa um temporizador de disparo único (one-shot) utilizando o microcontrolador Raspberry Pi Pico W e a função `add_alarm_in_ms()` do Pico SDK. O sistema aciona uma sequência de LEDs a partir do clique em um botão. Ao pressionar o botão, os três LEDs (azul, vermelho e verde) são imediatamente ligados, e, a cada 3 segundos, um LED é desligado até que todos estejam apagados. Durante a execução da sequência, o botão fica inativo para evitar reinicializações indesejadas.

## Objetivo
Implementar um sistema temporizador onde, após o acionamento por um botão, os LEDs mudam de estado em intervalos de 3 segundos. A sequência é iniciada apenas se não houver uma sequência em andamento e utiliza callbacks de alarme para gerenciar o temporizador, seguindo os requisitos descritos na atividade.

## Componentes Utilizados
1. **Microcontrolador:** Raspberry Pi Pico W
2. **LEDs:** 3 LEDs (Azul, Vermelho e Verde)
3. **Resistores:** 3 resistores de 330 Ω
4. **Botão (Pushbutton):** para disparo da sequência
5. **Ambiente de Simulação:** Wokwi e BitDogLab (opcional para experimentos com LED RGB e Botão A nos GPIOs 11, 12, 13 e 05)

## Requisitos
1. Ao pressionar o botão, os três LEDs devem ser ligados simultaneamente.
2. Utilizando a função `add_alarm_in_ms()`, a cada 3.000 ms ocorre uma mudança na sequência de acionamento dos LEDs:
   - Primeiro, o LED azul é desligado.
   - Depois, o LED vermelho é desligado.
   - Por fim, o LED verde é desligado, finalizando a sequência.
3. Durante a execução da sequência temporizada, o botão não pode iniciar uma nova sequência.
4. Implementação de um mecanismo de debounce para evitar múltiplos acionamentos indevidos do botão.

## Estrutura do Código
O código está organizado da seguinte forma:

- **Definição de pinos e constantes:**  
  Os LEDs estão associados aos GPIOs 11 (azul), 12 (vermelho) e 13 (verde), e o botão ao GPIO 5. O atraso entre as etapas da sequência é definido em 3000 ms.

- **Funções de Callback:**  
  São implementadas três funções de callback:
  - `callback_stage1()`: Desliga o LED azul e agenda `callback_stage2()`.
  - `callback_stage2()`: Desliga o LED vermelho e agenda `callback_stage3()`.
  - `callback_stage3()`: Desliga o LED verde e finaliza a sequência, permitindo nova ativação.

- **Rotina de Interrupção do Botão:**  
  A função `button_callback()` trata a interrupção do botão, implementa debounce e verifica se já existe uma sequência em execução. Se não houver, liga todos os LEDs e inicia a sequência temporizada.

- **Setup e Loop Principal:**  
  A função `setup()` configura os pinos GPIO para os LEDs e o botão, e habilita a interrupção para o botão. No `main()`, o programa entra em um loop infinito utilizando `tight_loop_contents()` para manter o microcontrolador ativo.

## Como Executar
1. Configure o ambiente de desenvolvimento com o Pico SDK.
2. Compile o código utilizando as ferramentas apropriadas para o Raspberry Pi Pico W.
3. Execute a simulação no Wokwi ou no BitDogLab para observar:
   - A ativação da sequência dos LEDs ao pressionar o botão.
   - A alteração dos estados dos LEDs a cada 3 segundos conforme descrito.
4. Opcionalmente, carregue o firmware no microcontrolador.
5. Verifique que, durante a sequência, o botão não reinicia o processo até que a última etapa seja concluída.

