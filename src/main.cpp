#include "Database.h"
#include <Arduino.h>
#include <Bounce2.h>

Bounce button;

#include <WiFi.h>

#include "WebServer.h"
#include "MacroStorage.h"
#include "MacroManager.h"

#include "USB.h"
#include "USBHIDKeyboard.h"

#include "KeyboardActions.h"
#include "CommandTable.h"
#include "MacroEngine.h"



USBHIDKeyboard Keyboard;



KeyboardActions keyboardActions(&Keyboard);

CommandTable commandTable(&keyboardActions);

MacroEngine macro(&commandTable);


WebServerManager webServer;


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

void startAccessPoint();

//===============================
// Setup
//===============================

void setup(){

    
    Serial.begin(115200);
    Serial.setTimeout(0);
    
    Database_init();
    if(Database_isFirstRun()){
        Serial.println("First Run DataBase.");
    }

    USB.begin();
    Keyboard.begin();
    Serial.println("USB Keyboard Started");

    startAccessPoint();
    MacroStorage::instance().begin();
    MacroManager::instance().begin();
    webServer.begin();

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

void startAccessPoint(){
    WiFi.mode(WIFI_AP);
    db_ap_wifi_conf_t *ap = Database_get_ap();
    String AP_SSID = String(ap->ssid);
    String AP_PASS = String(ap->pass);
    if (!WiFi.softAP(AP_SSID, AP_PASS))
    {
        Serial.println("Failed to start Access Point");
        return;
    }

    Serial.println("Access Point Started");
    Serial.print("SSID: ");
    Serial.println(AP_SSID);

    Serial.print("Password: ");
    Serial.println(AP_PASS);

    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
}


void keyInit(void){
    button.attach(GPIO_NUM_0, INPUT_PULLUP);
    button.interval(20);
    Serial.println("[Key] initialized correctly.");
}
void keyProcess(void){
    button.update();

    if (button.fell()){
        Serial.printf("[Key] Num: %d, Pressed\n", button.getPin());
        macro.run(script);
    }
    
    if (button.rose()){
        Serial.printf("[Key] Num: %d, Released\n", button.getPin());
    }
}
