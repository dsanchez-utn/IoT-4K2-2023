// Este Bot sólo repite el mensaje recibido

// Código para luego concatenar con "Serial <<  "
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotDefines.h>
#include <CTBotInlineKeyboard.h>
#include <CTBotReplyKeyboard.h>
#include <CTBotSecureConnection.h>
#include <CTBotStatusPin.h>
#include <CTBotWifiSetup.h>
#include <Utilities.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

CTBot miBot;

#include "token.h"


void setup() {
  Serial.begin(115200);
  Serial.print("Iniciando Bot de Telegram");

  miBot.wifiConnect(ssid, password);
  miBot.setTelegramToken(token);

  if (miBot.testConnection()) {
    Serial.println("\n Conectado");
  }
  else {
    Serial.println("\n No resultó bien");
  }
}

void loop() {
  TBMessage msg;

  if (CTBotMessageText == miBot.getNewMessage(msg)) {
    Serial << "Mensaje: " << msg.sender.firstName << " - " << msg.text << "\n";
    miBot.sendMessage(msg.sender.id, msg.text);
  }
  delay(500);
}
