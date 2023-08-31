
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop(){
  // aumenta el brillo
  for(int ciclo = 0; ciclo <= 255; ciclo++){
    analogWrite(LED_BUILTIN, ciclo);
    delay(5);
  }
  // disminuye el brillo
  for(int ciclo = 255; ciclo >= 0; ciclo--){
    analogWrite(LED_BUILTIN, ciclo);
    delay(5);
  }
  delay(1000);
}
