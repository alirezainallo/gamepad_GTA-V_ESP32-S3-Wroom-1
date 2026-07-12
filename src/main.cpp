#include <Arduino.h>
// #ifndef ARDUINO_USB_MODE
// #error This ESP32 SoC has no Native USB interface
// #elif ARDUINO_USB_MODE == 1
// #warning This sketch should be used when USB is in OTG mode
// void setup() {}
// void loop() {}
// #else

#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

uint32_t lastSend = 0;
const uint32_t interval = 3000; // send every 3 seconds


void setup() {

  Serial.begin(115200);

  // Start USB HID keyboard
  USB.begin();
  Keyboard.begin();

  Serial.println("USB Keyboard Started");
}


void loop() {

  uint32_t now = millis();

  if (now - lastSend >= interval)
  {
    lastSend = now;

    Keyboard.write('A');

    Serial.println("Sent: A");
  }

}

// #endif