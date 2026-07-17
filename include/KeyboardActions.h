#ifndef KEYBOARD_ACTIONS_H
#define KEYBOARD_ACTIONS_H

#include <Arduino.h>
#include "USBHIDKeyboard.h"


#define KEY_GTA_CHEAT   0x60

class KeyboardActions
{
private:
    USBHIDKeyboard *keyboard;

public:
    KeyboardActions(USBHIDKeyboard *kbd);

    void typeText(const String &text);
    void press(uint8_t key);
    void pressCombo(uint8_t modifier, uint8_t key);
    void pressKey(const String &key);
};

#endif
