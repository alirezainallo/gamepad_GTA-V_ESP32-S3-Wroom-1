#include <Arduino.h>

#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

uint32_t lastAction = 0;
const uint32_t interval = 1000; // 5 seconds


void setup()
{
    Serial.begin(115200);

    USB.begin();
    Keyboard.begin();

    Serial.println("USB Keyboard Started");
}

void keyChecker()
{
    static uint32_t cnter = 0;
  Serial.println("Opening Chrome...");
  
  // Press Windows key
  // Keyboard.press(KEY_LEFT_GUI); // Windows key (left)
  // delay(50);
  // Keyboard.release(KEY_LEFT_GUI); // Release Windows key
  // Keyboard.press(KEY_RIGHT_GUI); // Windows key (left)
  // delay(50);
  // Keyboard.release(KEY_RIGHT_GUI); // Release Windows key
  Keyboard.printf("cnter: %d:", cnter);
  
  delay(200);

  Keyboard.write(cnter);  // write یعنی press + release با هم
//   Keyboard.write(KEY_LEFT_GUI);  // write یعنی press + release با هم

  delay(200);
  
  // Type chrome
  
  // Press Enter
  // Keyboard.press(KEY_RETURN);
  // delay(50);
  // Keyboard.release(KEY_RETURN);
  Keyboard.write(KEY_RETURN);  // write یعنی press + release با همchrome
  
  cnter += 1;

  Serial.println("Done");
}


void openChrome()
{
  Serial.println("Opening Chrome...");
  
  // Press Windows key
  // Keyboard.press(KEY_LEFT_GUI); // Windows key (left)
  // delay(50);
  // Keyboard.release(KEY_LEFT_GUI); // Release Windows key
  // Keyboard.press(KEY_RIGHT_GUI); // Windows key (left)
  // delay(50);
  // Keyboard.release(KEY_RIGHT_GUI); // Release Windows key
  Keyboard.write(93);  // write یعنی press + release با هم
//   Keyboard.write(KEY_LEFT_GUI);  // write یعنی press + release با هم

  delay(500);
  
  // Type chrome
  Keyboard.print("chrome");
  
  delay(200);
  
  // Press Enter
  // Keyboard.press(KEY_RETURN);
  // delay(50);
  // Keyboard.release(KEY_RETURN);
  Keyboard.write(KEY_RETURN);  // write یعنی press + release با همchrome
  
  Serial.println("Done");
}

void loop()
{
    uint32_t now = millis();

    if (now - lastAction >= interval)
    {
        lastAction = now;

        // openChrome();
        keyChecker();
    }
}