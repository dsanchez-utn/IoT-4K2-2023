//#include <Adafruit_SSD1306.h>
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

void setup() {
  Serial.begin(BAUDRATE);
  delay(1000);
  Serial.println(F("Iniciando Display..."));
  displayInit();  
  Serial.println(F("Display Iniciado"));
  delay(5000);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("Han pasado %d seg.\n",millis()/1000);
  display.display();

  Serial.println(millis());
  delay(random(2000));
}
