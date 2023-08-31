
// ESP32 Touch Test
// Touch0 es T0 en el pin GPIO 4.

void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.println("Sensor Touch");
}

void loop() {
  Serial.println(touchRead(4));  // toma valor del Touch 4 pin = GPIO13
  delay(1000);
}