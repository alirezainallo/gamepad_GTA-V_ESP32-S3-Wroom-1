#include <Arduino.h>

#include "USB.h"
#include "USBHIDKeyboard.h"

#include "KeyboardActions.h"
#include "CommandTable.h"
#include "MacroEngine.h"



USBHIDKeyboard Keyboard;



KeyboardActions keyboardActions(&Keyboard);

CommandTable commandTable(&keyboardActions);

MacroEngine macro(&commandTable);



//===============================
// Macro Script
//===============================

String script =

"win\n"
"delay 500\n"
"type chrome\n"
"delay 500\n"
"enter\n";




//===============================
// Setup
//===============================

void setup()
{

    Serial.begin(115200);


    USB.begin();

    Keyboard.begin();


    Serial.println("USB Keyboard Started");


    // Wait for USB host
    delay(3000);



    macro.run(script);


}




//===============================
// Loop
//===============================

void loop()
{

}