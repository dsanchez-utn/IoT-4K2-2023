
const int pinBoton = 19; // Pin del pulsador
int estadoLed = LOW; // Estado del LED
int ultimoEstado = HIGH; // Estado anterior del pulsador

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Configurar el pin del LED INTEGRADO como salida
  pinMode(pinBoton, INPUT_PULLUP); // Configurar el pin del pulsador como entrada
  Serial.begin(115200);
}

void loop() {
  // Leer el estado del pulsador
  int lectura = digitalRead(pinBoton);
  // Toma la lectura del pulsador
  if (lectura != ultimoEstado) {

    // Si el pulsador ha sido presionado, cambiar el estado del LED
    if (lectura == HIGH) {
      estadoLed = !estadoLed;
      digitalWrite(LED_BUILTIN, estadoLed);
      //digitalWrite(23, estadoLed);
    }
  }
  // Guardar el último estado del pulsador
  ultimoEstado = lectura;
  delay(50);
}















/*
//const int ledPin = 2; // Pin del LED
const int pinBoton = 19; // Pin del pulsador
int estadoLed = LOW; // Estado del LED
int estadoBoton; // Estado del pulsador
int ultimoEstado = LOW; // Estado anterior del pulsador

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Configurar el pin del LED como salida
  pinMode(pinBoton, INPUT_PULLUP); // Configurar el pin del pulsador como entrada
}

void loop() {
  // Leer el estado del pulsador
  int lectura = digitalRead(pinBoton);

  if (lectura != ultimoEstado) {
    // Si el estado del pulsador ha cambiado, actualizar el estado del LED
    if (lectura != estadoBoton) {
      estadoBoton = lectura;

      // Si el pulsador ha sido presionado, cambiar el estado del LED
      if (estadoBoton == HIGH) {
        estadoLed = !estadoLed;
        digitalWrite(LED_BUILTIN, estadoLed);
      }
    }
  }
  // Guardar el último estado del pulsador
  ultimoEstado = lectura;
//  delay(100);
}

*/