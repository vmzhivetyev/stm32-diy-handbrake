#include <Arduino.h>

int8_t led = 0;

void setup() {
  SerialUSB.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(SerialUSB.available()) {
    char c = SerialUSB.read();
    SerialUSB.print("hello ");
    SerialUSB.print(c);
    SerialUSB.println();
  }
  led = ~ led & 1;
  digitalWrite(LED_BUILTIN, led);
  delay(100);
}