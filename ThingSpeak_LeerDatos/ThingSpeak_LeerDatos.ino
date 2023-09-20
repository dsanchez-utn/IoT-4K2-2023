#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient  client;

// variables de canal privado
//unsigned long nroCanalPublico = SECRET_CH_ID_PUBLIC;
//unsigned int nroCampoPublico = 1;


// variables de canal público
unsigned long nroCanalPrivado = SECRET_CH_ID_PRIVATE;
const char * ReadAPIKey = SECRET_READ_APIKEY;
unsigned int nroCampoPrivado = 2; 

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);
}

void loop() {

  int statusCode = 0;
  
  // Connecta a WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Conectando a: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnectado");
  }

  // Lee un campo de Canal Privado
  float temperatureInF = ThingSpeak.readLongField(nroCanalPrivado, nroCampoPrivado, ReadAPIKey);

  // Checkea lectura
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Temperatura en Canal de ThingSpeak: " + String(temperatureInF) + " °C");
  }
  else{
    Serial.println("Problemas leyendo el canal. HTTP error code " + String(statusCode)); 
  }
  
  delay(5000);
/*
  // Lee un campo de canal público  
  long count = ThingSpeak.readFloatField(nroCanalPublico, nroCampoPublico);
*/  
}