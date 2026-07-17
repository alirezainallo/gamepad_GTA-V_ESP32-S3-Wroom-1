#include "KeyboardActions.h"


KeyboardActions::KeyboardActions(USBHIDKeyboard *kbd)
{
    keyboard = kbd;
}


void KeyboardActions::typeText(const String &text)
{
    keyboard->print(text);
}


void KeyboardActions::press(uint8_t key)
{
    // keyboard->write(key);
    keyboard->press(key);
    delay(35);
    keyboard->release(key);
}


void KeyboardActions::pressCombo(uint8_t modifier, uint8_t key)
{
    keyboard->press(modifier);
    keyboard->press(key);

    delay(20);

    keyboard->releaseAll();
}


void KeyboardActions::pressKey(const String &key)
{
    String k = key;
    k.toLowerCase();


    // Normal keys
    if (k == "enter"){
        press(KEY_RETURN);
    }

    else if (k == "`"){
        press(KEY_GTA_CHEAT);
    }

    else if (k == "tab")
        press(KEY_TAB);
        
    else if (k == "win"){
        // // press(HID_KEY_GUI_LEFT);
        // press(KEY_LEFT_GUI);
        // // press(KEY_RIGHT_GUI);
        keyboard->pressRaw(HID_KEY_GUI_LEFT); // Left GUI
        delay(150);
        keyboard->releaseRaw(HID_KEY_GUI_LEFT);

        //// for "win + r"
        // keyboard->press(KEY_LEFT_GUI);
        // delay(20);
        // keyboard->press('r');  // Win + R برای باز کردن Run
        // keyboard->releaseAll();
    }

    else if (k == "space")
        press(HID_KEY_SPACE);

    else if (k == "backspace")
        press(HID_KEY_BACKSPACE);

    else if (k == "delete")
        press(KEY_DELETE);

    else if (k == "esc")
        press(KEY_ESC);
    

    // Navigation keys
    else if (k == "up")
        press(KEY_UP_ARROW);

    else if (k == "down")
        press(KEY_DOWN_ARROW);

    else if (k == "left")
        press(KEY_LEFT_ARROW);

    else if (k == "right")
        press(KEY_RIGHT_ARROW);


    else if (k == "home")
        press(KEY_HOME);

    else if (k == "end")
        press(KEY_END);

    else if (k == "pageup")
        press(KEY_PAGE_UP);

    else if (k == "pagedown")
        press(KEY_PAGE_DOWN);


    // Locks
    else if (k == "capslock")
        press(KEY_CAPS_LOCK);

    else if (k == "numlock")
        press(HID_KEY_NUM_LOCK);


    // Function keys
    else if (k == "f1")
        press(KEY_F1);

    else if (k == "f2")
        press(KEY_F2);

    else if (k == "f3")
        press(KEY_F3);

    else if (k == "f4")
        press(KEY_F4);

    else if (k == "f5")
        press(KEY_F5);

    else if (k == "f6")
        press(KEY_F6);

    else if (k == "f7")
        press(KEY_F7);

    else if (k == "f8")
        press(KEY_F8);

    else if (k == "f9")
        press(KEY_F9);

    else if (k == "f10")
        press(KEY_F10);

    else if (k == "f11")
        press(KEY_F11);

    else if (k == "f12")
        press(KEY_F12);


    delay(30);
}
