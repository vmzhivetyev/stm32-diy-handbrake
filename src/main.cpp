#include <Arduino.h>
#include <USBComposite.h>

USBHID HID;
HIDJoystick Joystick(HID);

#define POTENTIOMETER_PIN A0

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  HID.begin(HID_JOYSTICK);
  while (!USBComposite);
}

void loop() {
  delay(10);
  Joystick.X(millis() % 1024);
}
