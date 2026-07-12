#include <Arduino.h>

// put function declarations here:
void heartBit(uint32_t ms);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(0);
  Serial.println("Starting...");
  // pinMode(43, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  heartBit(1000); // Call heartBit every 1000 milliseconds
}

// put function definitions here:
void heartBit(uint32_t ms){
  static uint32_t next = 0;
  static uint32_t curr = 0;
  curr = millis();
  if(next < curr){
    next = curr + ms/2;
    // digitalWrite(43, !digitalRead(43));
    Serial.println("Heartbeat");
  }
}