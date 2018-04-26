#include <Arduino.h>
#include "email/email.h"
//Programa: Monitoracao de planta usando Arduino
//Autor: FILIPEFLOP

#define pino_sinal_analogico A0
#define pino_led_vermelho 5
#define pino_led_amarelo 6
#define pino_led_verde 7
#define pino_buzzer 8
#define ONE_SECOND 1000

uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
IPAddress ip(192, 168, 1, 25);
byte server[] = {00,00,00,00}; // Colocar o ip do servidor SMTP
EthernetClient client;

typedef enum {UMIDO, MODERADO, SECO} umidade;
umidade status = SECO;

int valor_analogico;

void setup()
{
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);
  pinMode(pino_buzzer, OUTPUT);
  Serial.begin(9600);

  while(!Serial) {
    // Aguarda...
  }

//INICIO CONEXAO COM A WEB
  Serial.println("Iniciando conexão DHCP");
  if(Ethernet.begin(mac) == 0) {
    Serial.println("Falha ao configurar Ethernet usando DHCP com MAC");
    Ethernet.begin(mac, ip);
  }

  Serial.println(client.connected());

  delay(ONE_SECOND);
}

void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}

void loop()
{

  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(pino_sinal_analogico);

  //Mostra o valor da porta analogica no serial monitor
  // Serial.print("Porta analogica: ");
  // Serial.print(valor_analogico);

  //Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    
    if(status != UMIDO) {
        Serial.println(" Status: Solo umido");
        status = UMIDO;
    }
    
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
    noTone(pino_buzzer);
  }

  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    if(status != MODERADO){
        Serial.println(" Status: Umidade moderada");
        status = MODERADO;
    }
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
    // tone(pino_buzzer, 1000);
  }

  //Solo seco, acende led vermelho
  if (valor_analogico > 800 && valor_analogico < 1024)
  {

    if(status != SECO) {
      Serial.println(" Status: Solo seco");
      status = SECO;

      // envia(); // Envia email...
    }
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
    // tone(pino_buzzer, 1500);
  }

  delay(ONE_SECOND);
}