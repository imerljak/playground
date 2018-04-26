#include "email.h"


void recebe(EthernetClient client){
  while (client.available()){
    char conteudo = client.read();
    Serial.print(conteudo);
  }
}

void envia(EthernetClient client, int time, byte server[]){
  delay(time);
  Serial.println("conectando...");
  if (client.connect(server, 587)){
    Serial.println("conectado!");
    Serial.println("enviando email...");
    Serial.println();
    client.println("HELO localhost");
    recebe(client);
    delay(time);
    client.println("AUTH LOGIN");
    recebe(client);
    delay(time);
    client.println(""); // Email de login em base de 64:
    recebe(client);
    delay(time);
    client.println(""); // Senha do email em base de 64:
    recebe(client);
    delay(time);
    client.println("mail from: <imerljak@gmail.com>"); //Email remetente
    recebe(client);
    delay(time);
    client.println("rcpt to: <imerljak@gmail.com>"); // Email destinatário
    recebe(client);
    delay(time);
    client.println("data");
    recebe(client);
    delay(time);
    client.println("Subject: Teste BYTE IP de Email!"); // Assunto
    recebe(client);
    delay(time);
    client.println("Testando email com arduino"); // Corpo
    recebe(client);
    delay(time);
    client.println("."); // Indica fim do email.
    recebe(client);
    delay(time);
    client.println();
    recebe(client);
    delay(time);
    Serial.println("email enviado!");
    delay(time);
    if (client.connected()){
      Serial.println();
      Serial.println("desconectando...");
      client.stop();
      Serial.println();
      Serial.println();
    }
  }else{
    Serial.println("connection failed");
  }
  Serial.println("Ready. Press 'e' to connect.");
}