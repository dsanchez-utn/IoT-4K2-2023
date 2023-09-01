#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <splash.h>
#include "config.h"

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void displayInit(){
  display.begin(0x3C, true); // Address 0x3C default
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.println(F("Hola Mundo!"));
  display.println(F("Datos de Compilacion:"));
  display.printf("Fecha %s\n",__DATE__);
  display.printf("Hora: %s\n",__TIME__);
  display.display();
}

void displayUpdateAndShow(unsigned long interval, float valorADC, float valorADC2){
	static unsigned long previousMillis = 0;
	unsigned long currentMillis = millis();
	
  if(currentMillis - previousMillis > interval) 
  {
		previousMillis = currentMillis;
    display.clearDisplay();
    display.setCursor(0,0);
//    display.printf("ADC: %.2f\n",valorADC); 
    display.printf("ADC crudo: %.2f\n",valorADC);
    display.printf("ADC en Voltaje: %.2f\n", valorADC2); 
    display.display();
	}
}

void setup() {
  Serial.begin(BAUDRATE);
  Serial.println(F("Iniciando Display..."));
  displayInit();  
  Serial.println(F("Display Iniciado"));
  delay(1000);
  display.setCursor(0,0);
}

void loop() {
  float valorADC = analogRead(PIN_ADC);
  float valorADC2 = analogRead(PIN_ADC) * 3.3 / 4095.0;  
  displayUpdateAndShow(100, valorADC, valorADC2);
}



//  float valorADC = (float) map(analogRead(PIN_ADC), 0, 4095, 4095, 0);
//  float valorADC2 = (float) map(analogRead(PIN_ADC),0 ,4095, 4095, 0) * 3.3 / 4095.0;
