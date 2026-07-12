#include <Arduino.h>

// put function declarations here:
void heartBit(uint32_t ms);
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 38
#define RGB_COUNT 1

Adafruit_NeoPixel pixel(
    RGB_COUNT,
    RGB_PIN,
    NEO_GRB + NEO_KHZ800);

TaskHandle_t rgbTaskHandle;

void rgbTask(void *parameter)
{
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  while (true)
  {
    // قرمز
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));
    pixel.show();
    vTaskDelay(pdMS_TO_TICKS(500));

    // سبز
    pixel.setPixelColor(0, pixel.Color(0, 255, 0));
    pixel.show();
    vTaskDelay(pdMS_TO_TICKS(500));

    // آبی
    pixel.setPixelColor(0, pixel.Color(0, 0, 255));
    pixel.show();
    vTaskDelay(pdMS_TO_TICKS(500));

    // خاموش
    pixel.clear();
    pixel.show();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(0);
  Serial.println("Starting...");
  // pinMode(43, OUTPUT);


  pixel.begin();
  pixel.setBrightness(50);
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  pixel.show();

  // pixel.begin();
  // pixel.setBrightness(50);
  // pixel.clear();
  // pixel.show();

  // xTaskCreate(
  //     rgbTask,    // Task function
  //     "RGB Task", // Name
  //     2048,       // Stack size
  //     nullptr,
  //     1, // Priority
  //     &rgbTaskHandle);

  // Serial.println("RGB Task Started");
}

void loop()
{
  // put your main code here, to run repeatedly:
  heartBit(1000); // Call heartBit every 1000 milliseconds
}

// put function definitions here:
void heartBit(uint32_t ms)
{
  static uint32_t next = 0;
  static uint32_t curr = 0;
  curr = millis();
  if (next < curr)
  {
    next = curr + ms / 2;
    // digitalWrite(43, !digitalRead(43));
    Serial.println("Heartbeat");
  }
}