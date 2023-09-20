#include "ThingSpeak.h"
#include "WiFi.h"

#include "DHT.h"

#define pinDHT 33    //Pin del sensor

const char* ssid = "";
const char* password = "";

unsigned long channelID = 99999999;
const char* WriteAPIKey = "API KEY";

// Timer
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

WiFiClient cliente;

DHT dht(pinDHT, DHT22);


void setup() {
  Serial.begin(115200);
  Serial.println("Test de sensores:");

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conectado!");

  ThingSpeak.begin(cliente);

  dht.begin();

}

void loop() {

  if ((millis() - lastTime) > timerDelay) {
    leerdht();

    ThingSpeak.writeFields(channelID,WriteAPIKey);
    Serial.println("Datos enviados a ThingSpeak!");

    lastTime = millis();
  }
}

void leerdht() {
  
  float t2 = dht.readTemperature();
  float h2 = dht.readHumidity();

  while (isnan(t2) || isnan(h2)){
    Serial.println("Lectura fallida en el sensor DHT22, repitiendo lectura...");
    delay(2000);
    t2 = dht.readTemperature();
    h2 = dht.readHumidity();
  }

  Serial.print("Temperatura DHT22: ");
  Serial.print(t2);
  Serial.println(" ºC.");

  Serial.print("Humedad DHT22: ");
  Serial.print(h2);
  Serial.println(" %."); 

  Serial.println("-----------------------");

  ThingSpeak.setField (2,t2);
  ThingSpeak.setField (3,h2);

}