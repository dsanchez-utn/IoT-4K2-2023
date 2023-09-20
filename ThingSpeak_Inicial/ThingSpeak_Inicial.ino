#include "ThingSpeak.h"
#include "WiFi.h"

//Declarar funciones:
void process();

//Constantes:
const int led = 23;
const char * SSID = "ACNET2";
const char * PASS = "";

unsigned long channel = 2274848;
const char * writeAPIKey = "FXPPV47A789VL2A7"; 


//Objeto WIFI Client
WiFiClient client;

void setup() {
    // Activamos los pines de entrada y salida
    pinMode(led, OUTPUT);
    Serial.begin(115200);
    //Conectar WIFI:
    WiFi.begin(SSID, PASS);
    Serial.print("Conectando WIFI\n");
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.print("WIFI Conectado!");

    //Inicializar objeto ThingSpeak
    ThingSpeak.begin(client);

}
 
void loop() {
  process();
}


void process(){
  digitalWrite(led, HIGH);
  delay(2000);
  //Cada vez que se enciende el LED enviamos un valor aleatorio entre [0;100]
  int rand = random(1,100);

  Serial.printf("Enviando valor: %d  ", rand);
  
  digitalWrite(led, LOW);
  delay(2000); 
  
  int x = ThingSpeak.writeField(channel, 1, rand, writeAPIKey);
  if(x == 200){
    Serial.println("Canal escrito correctamente.");
  }
  else{
    Serial.println("Problemas al actualizar el canal. HTTP error code " + String(x));
  }
}





//  ThingSpeak.setField(1, rand);
//  ThingSpeak.writeFields(channel, writeAPIKey);

