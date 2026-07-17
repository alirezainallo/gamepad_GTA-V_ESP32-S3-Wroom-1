#include "Database.h"
#include <Arduino.h>
#include <Bounce2.h>
#include <LittleFS.h>

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

// String script =
// "key `\n"
// "type painkiller\n"
// "delay 23\n"
// "key enter\n";
String script =
"key win\n"
"type chrome\n"
"delay 23\n"
"key enter\n";


// "delay 32\n"
// "type `\n"
// "delay 20\n"
// "enter\n"
// "type turtle\n"
// "type offroad\n"
// "type rapidgt\n"
// "type catchme\n"
// "type catchmebuzzoff\n"


void keyInit(void);
void keyProcess(void);

void startAccessPoint();
void connectWiFi();

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

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

    // LittleFS.begin(true);
    // listDir(LittleFS, "/", 0);
    // while(true)delay(1000);

    USB.begin();
    Keyboard.begin();
    Serial.println("USB Keyboard Started");

    // connectWiFi();
    startAccessPoint();
    MacroStorage::instance().begin();
    MacroManager::instance().begin();
    webServer.begin();

    // Wait for USB host
    delay(3000);

    Serial.println("----------------------------");
    Serial.println("list files:");
    listDir(LittleFS, "/", 0);
    Serial.println("----------------------------");

    // macro.run(script);


    keyInit();
}




//===============================
// Loop
//===============================

void loop(){
    keyProcess();
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void startAccessPoint(){
    WiFi.mode(WIFI_AP);
    db_ap_wifi_conf_t *ap = Database_get_ap();
    String AP_SSID = String(ap->ssid);
    String AP_PASS = String(ap->pass);
    // if (!WiFi.softAP(AP_SSID, AP_PASS))
    if (!WiFi.softAP(AP_SSID))
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
void connectWiFi() {
    WiFi.mode(WIFI_STA);
    db_sta_wifi_conf_t *sta = Database_get_sta();
    String WIFI_SSID = String(sta->ssid);
    String WIFI_PASS = String(sta->pass);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
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
