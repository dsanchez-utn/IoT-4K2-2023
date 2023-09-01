//const int ledPin = 2; // Pin del LED
const int pinBoton = 19; // Pin del pulsador
int estadoLed = LOW; // Estado del LED   
int estadoBoton; // Estado del pulsador
int ultimoEstado = HIGH; // Estado anterior del pulsador   
unsigned long ultimoRebote = 0; // Último tiempo de rebote del pulsador
int delayRebote = 50; // Tiempo de rebote del pulsador

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Configurar el pin del LED como salida
  pinMode(pinBoton, INPUT_PULLUP); // Configurar el pin del pulsador como entrada
  Serial.begin(115200);
}

void loop() {
  // Leer el estado del pulsador
  int lectura = digitalRead(pinBoton);

  // Si el estado del pulsador ha cambiado, registrar el tiempo de rebote
  if (lectura != ultimoEstado) {
    ultimoRebote = millis();
  }

  // Si ha pasado suficiente tiempo desde el último rebote, actualizar el estado del pulsador
  if ((millis() - ultimoRebote) > delayRebote) {
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
}