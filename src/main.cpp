#include <Arduino.h>
#include <USBComposite.h>

USBHID HID;
HIDJoystick Joystick(HID);

#define POTENTIOMETER_PIN PA0
#define BUTTON1_PIN PB0
#define BUTTON2_PIN PB1

void setup() {
  HID.begin(HID_JOYSTICK);
  while (!USBComposite);

  pinMode(POTENTIOMETER_PIN, INPUT_ANALOG);
  pinMode(BUTTON1_PIN, INPUT_PULLDOWN);
  pinMode(BUTTON2_PIN, INPUT_PULLDOWN);
}

void loop() {
  float val = analogRead(POTENTIOMETER_PIN) / 4 / 0.7f; // 0–4095
  Joystick.X((uint16)val);

  Joystick.button(1, digitalRead(BUTTON1_PIN) == HIGH);
  Joystick.button(2, digitalRead(BUTTON2_PIN) == HIGH);
}
