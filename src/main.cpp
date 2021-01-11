#include <Arduino.h>

int8_t led = 0;

void setup() {
  // Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // if(Serial.available()) {
  //   char c = Serial.read();
  //   Serial.print("hello ");
  //   Serial.print(c);
  //   Serial.println();
  // }
  led = ~ led & 1;
  digitalWrite(LED_BUILTIN, led);
  delay(100);
}