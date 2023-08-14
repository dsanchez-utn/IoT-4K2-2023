int amplitud = 1000; //Amplitud de la onda senoidal
double w = 2 * 0.2 * 3.141593; //Frecuencia angular
int contador = 0;

void setup() {
  Serial.begin(115200); //Se inicia comunicacion serial
}
void loop() {
  //Mientras millis() sea mayor a 5000 milisegundos
  while (millis() >= 5000) {
    //Mientras millis() sea menor a 10000 segundos
    while (millis() <= 10000) {
      //Funcion millis transformada a tiempo (seg)
      double t = millis() * 0.001;
      //Calculo del valor puntual de la onda senoidal
      double num = amplitud * sin(w * t);
      //Se imprime el valor calculado
      Serial.println(num);
      delay(5);

    }
  delay(1000);
  contador++;
  Serial.print(contador);
  Serial.print("  ");
  Serial.println(millis());

  }

}









  /*
  delay(1000);
  Serial.print(contador);
  Serial.print("  ");
  Serial.println(millis());
  */




/*
  ;
  delay(1000);
  Serial.print(aumenta_contador());  //(contador);
  Serial.print("  ");
  Serial.println(millis());

  }
}

int aumenta_contador() {
  static int contador = 0;
  contador++;
  // contadorGlobal = contador + contadorGlobal;
  return contador;
}

*/







