/*INCLUSÃO DE BIBLIOTECAS*/
#include <DHT11.h>

/*INSTANCIANDO OBJETOS*/
DHT11 dht11(2); // Instanciando um objeto DHT11 conectado no pino digital 2

/*DECLARAÇÃO DE VARIÁVEIS*/
const int COOLER_PIN = 6; // Pino do cooler
int TEMP_LIMITE = 30; // Temperatura limite para ligar o cooler

void setup() {
  Serial.begin(9600); //INICIALIZANDO A COMUNICAÇÃO SERIAL (TAXA DE BITS QUE SERÁ PASSADO NA COMUNICAÇÃO)

  pinMode(COOLER_PIN, OUTPUT); // Configura o pino do cooler como saída

  digitalWrite(COOLER_PIN, LOW); // Inicia com o cooler desligado
}

void loop() {
    
  int temperature = dht11.readTemperature(); // Lê a temperatura E GUARDARÁ A TEMPERATURA NA VARIÁVEL TEMPERATURE.
  
  //este if 
  if (temperature != DHT11::ERROR_CHECKSUM &&
    temperature != DHT11::ERROR_TIMEOUT) {

    //irá imprimir no monitor serial a temperatura que foi lida.
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Se a temperatura alcançar ou ultrapassar a temperatura limite, o cooler será ativado.
    if (temperature >= TEMP_LIMITE) {
      delay(500); //aguarda meio segundo antes de ativar o cooler.
      digitalWrite(COOLER_PIN, HIGH); // Liga o cooler
      Serial.println("Cooler LIGADO");
    } else { //Quando a temperatura estiver abaixo do limite estabelecido, o cooler permanecerá desligado ou desligará.
      delay(500); //tempo de espera até desativar o cooler.
      digitalWrite(COOLER_PIN, LOW); // Desliga o cooler
      Serial.println("Cooler DESLIGADO");
    }

  } else {
    Serial.println("NÃO FOI POSSÍVEL DETECTAR A TEMPERATURA");
    // Serial.println(DHT11::getErrorString(temperature));
  }

  delay(2000); // Aguarda 2 segundos entre leituras
}
