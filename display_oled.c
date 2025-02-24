#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

// Definições dos pinos I2C
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Definição dos pinos dos botões
const uint BUTTON_A_PIN = 5;  // Botão A (simulação de detecção de som)
const uint BUTTON_B_PIN = 6;  // Botão B (desligar alarme)

// Definição dos pinos dos LEDs RGB
const uint RED_LED_PIN = 13;    // LED vermelho no GPIO 13
const uint GREEN_LED_PIN = 11;  // LED verde no GPIO 11
const uint BLUE_LED_PIN = 12;   // LED azul no GPIO 12

// Definição do pino do buzzer
const uint BUZZER_PIN = 21;  // Buzzer no GPIO 21 (conectado via transistor)

// Função para inicializar o hardware
void init_hardware() {
    // Configura os botões como entrada com pull-up
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    // Configura os LEDs RGB como saída
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    // Configura o pino do buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Inicialmente, desliga os LEDs RGB e o buzzer
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);
    gpio_put(BUZZER_PIN, 0);
}

// Função para piscar o LED verde (2 segundos)
void piscar_led_verde() {
    gpio_put(GREEN_LED_PIN, 1);  // Liga o LED verde
    sleep_ms(1000);              // Mantém ligado por 1 segundo
    gpio_put(GREEN_LED_PIN, 0);  // Desliga o LED verde
    sleep_ms(1000);              // Mantém desligado por 1 segundo
}

// Função para piscar o LED vermelho (0,5 segundos)
void piscar_led_vermelho() {
    gpio_put(RED_LED_PIN, 1);  // Liga o LED vermelho
    sleep_ms(250);             // Mantém ligado por 0,25 segundos
    gpio_put(RED_LED_PIN, 0);  // Desliga o LED vermelho
    sleep_ms(250);             // Mantém desligado por 0,25 segundos
}

// Função para gerar um sinal sonoro mais interessante
void gerar_bipe() {
    // Padrão de bipes: curto, curto, longo
    for (int i = 0; i < 2; i++) {
        gpio_put(BUZZER_PIN, 1);  // Liga o buzzer
        sleep_ms(100);            // Bipe curto (100 ms)
        gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
        sleep_ms(100);            // Intervalo entre bipes curtos
    }

    gpio_put(BUZZER_PIN, 1);  // Liga o buzzer
    sleep_ms(500);            // Bipe longo (500 ms)
    gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
    sleep_ms(200);            // Intervalo após o bipe longo
}

// Função para centralizar o texto no display
void centralizar_texto(uint8_t *buffer, const char *texto, int y) {
    int largura_texto = strlen(texto) * 6;  // Cada caractere tem 6 pixels de largura
    int x = (ssd1306_width - largura_texto) / 2 - 10;  // Calcula a posição x para centralizar
    ssd1306_draw_string(buffer, x, y, texto);
}

int main() {
    stdio_init_all();  // Inicializa os tipos stdio padrão presentes ligados ao binário

    // Inicializa o hardware
    init_hardware();

    // Inicialização do I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);  // Inicializa o I2C com o clock definido
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);  // Configura o pino SDA para função I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);  // Configura o pino SCL para função I2C
    gpio_pull_up(I2C_SDA);  // Habilita pull-up no pino SDA
    gpio_pull_up(I2C_SCL);  // Habilita pull-up no pino SCL

    // Inicialização do display SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column: 0,
        end_column: ssd1306_width - 1,
        start_page: 0,
        end_page: ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // Zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // Variável para controlar o estado do alarme
    bool alarme_ativo = false;

    // Loop principal
    while (true) {
        // Verifica se o Botão A foi pressionado (simulação de detecção de som)
        if (!gpio_get(BUTTON_A_PIN)) {
            alarme_ativo = true;  // Ativa o alarme
        }

        // Se o alarme estiver ativo
        if (alarme_ativo) {
            // Exibe a mensagem de alerta no display
            memset(ssd, 0, ssd1306_buffer_length);
            centralizar_texto(ssd, "Som Detectado!", 30);  // Centraliza o texto na vertical
            render_on_display(ssd, &frame_area);

            // Pisca o LED vermelho
            piscar_led_vermelho();

            // Gera o sinal sonoro
            gerar_bipe();

            // Verifica se o Botão B foi pressionado para desligar o alarme
            if (!gpio_get(BUTTON_B_PIN)) {
                alarme_ativo = false;  // Desativa o alarme

                // Limpa o display
                memset(ssd, 0, ssd1306_buffer_length);
                render_on_display(ssd, &frame_area);
            }
        } else {
            // Exibe a mensagem de status no display
            memset(ssd, 0, ssd1306_buffer_length);
            centralizar_texto(ssd, "Sistema Ativo", 30);  // Centraliza o texto na vertical
            render_on_display(ssd, &frame_area);

            // Pisca o LED verde
            piscar_led_verde();
        }

        // Aguarda 100 ms antes de verificar novamente
        sleep_ms(100);
    }

    return 0;
}