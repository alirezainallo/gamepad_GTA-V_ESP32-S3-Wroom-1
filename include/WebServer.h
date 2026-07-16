#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class WebServerManager
{
public:
    void begin();

private:
    AsyncWebServer server{80};

    void registerRoutes();
};
