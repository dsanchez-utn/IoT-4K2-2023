const int relayPin = 32;  //pin conectado a Señal del Rele
volatile int estadoPote;
volatile int entradaPin;

void setup(){
  Serial.begin(115200);
  pinMode(relayPin,OUTPUT);
  delay(2000);
}

void loop(){
  while (millis()< 100000) {
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(relayPin, LOW);
  delay(1000);
  }
}