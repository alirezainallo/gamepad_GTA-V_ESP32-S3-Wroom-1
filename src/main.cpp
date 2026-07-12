#include <Arduino.h>

#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

uint32_t lastAction = 0;
const uint32_t interval = 5000; // 5 seconds


void setup()
{
    Serial.begin(115200);

    USB.begin();
    Keyboard.begin();

    Serial.println("USB Keyboard Started");
}




void openChrome()
{
  Serial.println("Opening Chrome...");
  
  // Press Windows key
  Keyboard.press(KEY_LEFT_GUI); // Windows key (left)
  delay(50);
  Keyboard.release(KEY_LEFT_GUI); // Release Windows key
  // Keyboard.press(KEY_RIGHT_GUI); // Windows key (left)
  // delay(50);
  // Keyboard.release(KEY_RIGHT_GUI); // Release Windows key
  
  delay(500);
  
  // Type chrome
  Keyboard.print("chrome");
  
  delay(200);
  
  // Press Enter
  Keyboard.press(KEY_RETURN);
  delay(50);
  Keyboard.release(KEY_RETURN);
  
  Serial.println("Done");
}

void loop()
{
    uint32_t now = millis();

    if (now - lastAction >= interval)
    {
        lastAction = now;

        openChrome();
    }
}