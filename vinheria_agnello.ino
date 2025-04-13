#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C do LCD, 16 colunas e 2 linhas

const int pinoLDR = A3; // Pino analógico para o LDR
const int ledVerde = 11; // Pino digital para o LED verde
const int ledAmarelo = 10; // Pino digital para o LED amarelo
const int ledVermelho = 9; // Pino digital para o LED vermelho
const int buzzer = 6; // Pino digital para o buzzer

void setup() {
    lcd.init(); // Inicializa o LCD
    lcd.backlight(); // Liga a luz de fundo do LCD
    lcd.clear(); // Limpa o LCD

    lcd.setCursor(0, 0); // Define o cursor na primeira linha
    lcd.print("Vinheria Agnello"); // Exibe o nome da vinheria

    lcd.setCursor(0, 1); // Define o cursor na segunda linha
    lcd.print("Bem-vindo!"); // Exibe a mensagem de boas-vindas

    delay(3000); // Exibe por 3 segundos
    lcd.clear(); // Limpa o LCD

    pinMode(ledVerde, OUTPUT); // Define o pino do LED verde como saída
    pinMode(ledAmarelo, OUTPUT); // Define o pino do LED amarelo como saída
    pinMode(ledVermelho, OUTPUT); // Define o pino do LED vermelho como saída
    pinMode(buzzer, OUTPUT); // Define o pino do buzzer como saída
}

void loop() {
    int soma = 0; // Variável para armazenar a soma dos valores lidos

    for (int i = 0; i < 10; i++) {
        soma += analogRead(pinoLDR); // Lê o valor do LDR e adiciona à soma
        delay(100); // Aguarda 100ms entre as leituras
    }

    int leituraMedia = soma / 10; // Calcula a média das leituras

    int porcentagemLuz = map(leituraMedia, 0, 1023, 0, 100); // Mapeia o valor lido para porcentagem de luz

    lcd.setCursor(0, 0); // Define o cursor na primeira linha
    lcd.print("Luz: "); // Exibe a mensagem "Luz: "
    lcd.print(porcentagemLuz); // Exibe a porcentagem de luz
    lcd.print("%  "); // Exibe o símbolo de porcentagem

    if (porcentagemLuz <= 40) {
        digitalWrite(ledVerde, HIGH); // Liga o LED verde
        digitalWrite(ledAmarelo, LOW); // Desliga o LED amarelo
        digitalWrite(ledVermelho, LOW); // Desliga o LED vermelho
        noTone(buzzer); // Desliga o som do buzzer
    } else if (porcentagemLuz > 40 && porcentagemLuz <= 70) {
        digitalWrite(ledVerde, LOW); // Desliga o LED verde
        digitalWrite(ledAmarelo, HIGH); // Liga o LED amarelo
        digitalWrite(ledVermelho, LOW); // Desliga o LED vermelho
        noTone(buzzer); // Desliga o som do buzzer
    } else {
        digitalWrite(ledVerde, LOW); // Desliga o LED verde
        digitalWrite(ledAmarelo, LOW); // Desliga o LED amarelo
        digitalWrite(ledVermelho, HIGH); // Liga o LED vermelho
        tone(buzzer, 1000); // Liga o som do buzzer
        delay(3000); // Aguarda 3000ms
        noTone(buzzer); // Desliga o som do buzzer
    }

    delay(1000); // Aguarda 1 segundo
}