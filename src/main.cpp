#include <Arduino.h>
#include <USBComposite.h>

USBHID HID;
HIDJoystick Joystick(HID);

#define POTENTIOMETER_PIN PA0

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  HID.begin(HID_JOYSTICK);
  while (!USBComposite);

  pinMode(POTENTIOMETER_PIN, INPUT_ANALOG);
}

void loop() {
  float val = analogRead(POTENTIOMETER_PIN) / 4 / 0.7f; // 0–4095
  Joystick.X((uint16)val);
}
