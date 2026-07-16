#include "Database.h"
#include <Arduino.h>
#include <Bounce2.h>

Bounce button;

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

"tab\n"
"delay 50\n"
"type painkiller\n"
"delay 20\n"
"enter\n";


void keyInit(void);
void keyProcess(void);


//===============================
// Setup
//===============================

void setup(){

    Serial.begin(115200);
    Serial.setTimeout(0);


    USB.begin();

    Keyboard.begin();


    Serial.println("USB Keyboard Started");


    // Wait for USB host
    delay(3000);



    // macro.run(script);


    keyInit();
}




//===============================
// Loop
//===============================

void loop(){
    keyProcess();
}


void keyInit(void){
    button.attach(GPIO_NUM_0, INPUT_PULLUP);
    button.interval(20);
}
void keyProcess(void){
    button.update();

    if (button.fell()){
        Serial.println("Pressed");
        macro.run(script);
    }

    if (button.rose()){
        Serial.println("Released");
    }
}
