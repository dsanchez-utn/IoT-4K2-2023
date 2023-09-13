
// Instalar app para Android "Serial Bluetooth Terminal"

#include "BluetoothSerial.h"
#include "DHT.h"
#include <Adafruit_Sensor.h>

#define DHTPIN 33     // Digital pin connected to the DHT sensor    ...anteriormente DHTPIN 4
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT22   // DHT 11
// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;0

DHT dht(DHTPIN, DHTTYPE);

// Handle received and sent messages
String message = "";
char incomingChar;
String temperatureString = "";

// Timer: auxiliar variables
unsigned long previousMillis = 0;    // Almacena última publicación de Temepratura
const long interval = 5000;          // Intervalo que debe transcurrir para publicar las mediciones del sensor


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  dht.begin();
  
  SerialBT.begin("ESP32-BT");  // Con este nombre aparecerá el dispositivo al cual deberá conectarse con BT
  Serial.println();
  Serial.println("Dispositivo iniciado, ahora puede conectarse con bluetooth!");
}

void loop() {
  unsigned long currentMillis = millis();
  // Lee sólo cuando han pasado xxxx milisegundos
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }

    temperatureString = String(t) + "°C  " +  String(h) + "%  Humedad";
    SerialBT.println(temperatureString); 
  }
  // Lee mensajes recibidos (comandos para control del LED)
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  // Chequea mensajes recibidos
  if (message =="led on"){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (message =="led off"){
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(20);  
}