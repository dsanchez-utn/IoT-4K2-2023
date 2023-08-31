// set pin numbers
const int touchPin = 13; 
const int ledPin = 2;

// valor limite con el que cambia de estado
const int limite = 40;
// almacena el valor del pin Touch 
int valorTouch;

void setup(){
  Serial.begin(115200);
  delay(1000);
  pinMode (ledPin, OUTPUT);
  Serial.println("Sensor Touch controla LED");
}

void loop(){
  // lee el valor del pin touch
  valorTouch = touchRead(touchPin);
  Serial.print(valorTouch);
  
  if(valorTouch < limite){
    // enciende el LED
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED encendido");
  }
  else{
    // apaga el LED
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED apagado");
  }
  delay(500);
}