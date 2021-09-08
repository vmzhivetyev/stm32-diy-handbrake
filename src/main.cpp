#include <Arduino.h>
#include <USBComposite.h>
#include <HX711.h>

USBHID HID;
HIDJoystick Joystick(HID);

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN PB9
#define LOADCELL_SCK_PIN PB8

int8_t led = 0;

HX711 scale;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  HID.begin(HID_JOYSTICK);
  while (!USBComposite)
  {
    led = ~led & 1;
    digitalWrite(LED_BUILTIN, led);
    delay(500);
  }

  for (int i = 0; i < 10; i++)
  {
    led = ~led & 1;
    digitalWrite(LED_BUILTIN, led);
    delay(100);
  }

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(2280.f);
  scale.tare();
}

void loop() {
  float force = scale.get_units();
  float val = force / 600 * 4096; // 0–4095
  Joystick.X((uint16)val);
}
