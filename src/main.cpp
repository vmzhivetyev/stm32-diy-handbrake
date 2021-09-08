#include <Arduino.h>
#include <USBComposite.h>
#include <HX711.h>

USBHID HID;
HIDJoystick Joystick(HID);

#define POTENTIOMETER_PIN PA0
#define BUTTON1_PIN PB0
#define BUTTON2_PIN PB1


// HX711 circuit wiring
#define LOADCELL_DOUT_PIN PB9
#define LOADCELL_SCK_PIN PB8

int8_t led = 0;

HX711 scale;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  for (int i = 0; i < 15; i++) {
    Serial.print("waiting... ");
    Serial.println(i);
    delay(100);
    led = ~ led & 1;
    digitalWrite(LED_BUILTIN, led);
  }

  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  float force = scale.get_units();
  float val = force / 600 * 4096; // 0–4095
  Serial.print("raw: ");
  Serial.println(force);
  Serial.print("mapped: ");
  Serial.println(val);
  Serial.print("uint: ");
  Serial.println((uint16)val);

  // scale.power_down();			        // put the ADC in sleep mode
  delay(100);
  // scale.power_up();
}