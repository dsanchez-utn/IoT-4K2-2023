
const int touchMas = 12;   //Pin del Touch 5
const int touchMenos = 4;  //Pin del Touch 0
const int maximo = 255;
const int minimo = 0;
int estadoLed = 0;


volatile bool touchDetectado1 = false;  // Variable para indicar si se detectó un toque
volatile bool touchDetectado2 = false;  // Variable para indicar si se detectó un toque

void IRAM_ATTR handleTouch1() {   // almacena la funcion en memoria RAM en lugar de la flash para un rapido acceso
  touchDetectado1 = true;  // Establece la variable touchDetectado1 como verdadera al detectar un toque
}

void IRAM_ATTR handleTouch2() {
  touchDetectado2 = true;  // Establece la variable touchDetectado2 como verdadera al detectar un toque
}

void setup(){
  Serial.begin(115200);
  delay(1000);
  //pinMode(touchMas, INPUT);
  //pinMode(touchMenos, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);  
  //analogReadResolution(10);
  touchAttachInterrupt(touchMas, handleTouch1, 40);  // Asigna la función handleTouch1 como interrupción
  touchAttachInterrupt(touchMenos, handleTouch2, 40);  // Asigna la función handleTouch2 como interrupción

  touchAttachInterrupt(digitalPinToInterrupt(touchMas), handleTouch1, 40);  // Asigna la función handleTouch1 como interrupción
  touchAttachInterrupt(digitalPinToInterrupt(touchMenos), handleTouch2, 40);  // Asigna la función handleTouch1 como interrupción

}

void loop(){
  if (touchDetectado1) {
    estadoLed += 10;
    touchDetectado1 = false;
    estadoLed = min(estadoLed, maximo);
  } else if (touchDetectado2) {
    estadoLed -= 10;
    touchDetectado2 = false;
    estadoLed = max(estadoLed, minimo);
  }
  analogWrite(LED_BUILTIN, estadoLed);
  //Serial.println(estadoLed);
  Serial.printf("PWM:%d   Touch(+):%d Touch(-):%d \n",estadoLed,touchRead(touchMas),touchRead(touchMenos));  
  delay(100);
}






//  Serial.printf("PWM:%d   Touch(+):%d Touch(-):%d \n",estadoLed,touchRead(touchMas),touchRead(touchMenos));
