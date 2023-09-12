#include <WiFi.h>
//#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <splash.h>
#include "config.h"

//Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

WiFiServer server(80);

const char* ssid = "ACNET2";
const char* password = "";

String header;  // Variable para guardar el HTTP request
const int PIN_RELAY = 2 ;   //26;
int contador = 0;

//------------------------CODIGO HTML------------------------------
String pagina = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta charset='utf-8' />"
                "<title>Servidor Web ESP32</title>"
                "</head>"
                "<body>"
                "<center>"
                "<h1>Servidor Web ESP32</h1>"
                "<p><a href='/on'><button style='height:50px;width:150px;color:green'>ON</button></a></p>"
                "<p><a href='/off'><button style='height:50px;width:150px;color:red'>OFF</button></a></p>"
                "</center>"
                "</body>"
                "</html>";

String paginaOn = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta charset='utf-8' />"
                "<title>Servidor Web ESP32</title>"
                "</head>"
                "<body>"
                "<center>"
                "<h1>Servidor Web ESP32</h1>"
                "<p><a href='/on'><button style='height:50px;width:150px;color:green'>Activado</button></a></p>"
                "<p><a href='/off'><button style='height:50px;width:150px;color:red'>OFF</button></a></p>"
                "</center>"
                "</body>"
                "</html>";

String paginaOff = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta charset='utf-8' />"
                "<title>Servidor Web ESP32</title>"
                "</head>"
                "<body>"
                "<center>"
                "<h1>Servidor Web ESP32</h1>"
                "<p><a href='/on'><button style='height:50px;width:150px;color:green'>ON</button></a></p>"
                "<p><a href='/off'><button style='height:50px;width:150px;color:red'>Desactivado</button></a></p>"
                "</center>"
                "</body>"
                "</html>";

void displayInit(){
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.begin(0x3C, true); // Address 0x3C default
  display.clearDisplay();
  display.setTextSize(1);
//  display.setTextColor(SSD1306_WHITE);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  
  display.print("SSID:  ");
  display.println(WiFi.SSID());
  display.print("ID:   ");
  display.println(WiFi.localIP());

  display.display();
}


void setup() {
  Serial.begin(115200);
  Serial.println("");

  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 500 milisegundos para preguntar nuevemante si se puede conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("SSID:  ");
  Serial.println(WiFi.SSID());
  Serial.print("ID:   ");
  Serial.println(WiFi.localIP());
  server.begin();  // iniciamos el servidor
  displayInit();  
}

void loop() {
  WiFiClient client = server.available();  // Escucha a los clientes entrantes. Verifica si hay alguna solicitud de conexión pendiente

  if (client) {                     // Si se conecta un nuevo cliente

    //Serial.println("NUEVO CLIENTE conectado");

    String currentLine = "";        //
    while (client.connected()) {    // loop mientras el cliente está conectado
      if (client.available()) {     // si hay bytes para leer desde el cliente. Devuelve el número de bytes disponibles para lectura en el búfer de entrada del cliente
        char c = client.read();     // lee un byte
        header += c;
        if (c == '\n') {  // si el byte es un caracter de salto de linea
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");        //la solicitud HTTP se ha procesado correctamente.
            client.println("Content-type:text/html"); //establece el tipo de contenido que se enviará al cliente en la respuesta. En este caso se trata de una página HTML.
            client.println("Connection: close");      //la conexión entre el servidor y el cliente se cerrará después de enviar la respuesta
            client.println();

            // enciende y apaga el GPIO
            if (header.indexOf("GET /on") >= 0) {   //busca la primera aparición de "GET /on" y devuelve la posición donde se encuentra. Si no se encuentra devuelve -1
              digitalWrite(PIN_RELAY, HIGH);
              client.println(paginaOn);
              contador++;

            } else if (header.indexOf("GET /off") >= 0) {
              digitalWrite(PIN_RELAY, LOW);
              client.println(paginaOff);
              contador++;
            } else {
               client.println(pagina);
            }

            // Muestra la página web
           // client.println(pagina);
           // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else {  // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    display.clearDisplay();
    display.setCursor(0,16);
    display.printf("Solicitudes: %d\n", contador);
    display.display();
    
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
  }
}
