const short  PIN_PULSADOR = 19;

// bool encendido;

void setup() {
  Serial.begin(115200);
  Serial.println("Hola, 4K2!");
  pinMode(PIN_PULSADOR, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
//  encendido = digitalRead(PIN_PULSADOR);
  digitalWrite(LED_BUILTIN, !digitalRead(PIN_PULSADOR));   // actúa sobre el LED;
  Serial.printf("Pulsador:  %u  \n", digitalRead(PIN_PULSADOR));
  delay(100);
}













/*
    if (digitalRead(PIN_PULSADOR) == LOW) {
    encendido = true; 
    Serial.println("Encendido");
    
    } else {
      encendido = false; 
      Serial.println("Apagado!");
    }
*/
