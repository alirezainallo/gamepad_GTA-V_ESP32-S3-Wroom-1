#pragma once

#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

class Api
{
public:

    static void getKeys(AsyncWebServerRequest *request);

    static void executeKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);

    static void addKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);

    static void editKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);

    static void deleteKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);

private:

    static void sendSuccess(
        AsyncWebServerRequest *request);

    static void sendError(
        AsyncWebServerRequest *request,
        const char *message,
        uint16_t code = 400);
};
