#include "WebServer.h"

#include <LittleFS.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "Api.h"

void WebServerManager::begin()
{
    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS mount failed");
        return;
    }

    registerRoutes();

    server.begin();

    Serial.println("WebServer Started");
}

void WebServerManager::registerRoutes()
{
    /* ==========================
     * Static Files
     * ========================== */

    server.serveStatic("/", LittleFS, "/")
        .setDefaultFile("index.html");

    /* ==========================
     * API
     * ========================== */

    server.on(
        "/api/keys",
        HTTP_GET,
        Api::getKeys);

    /* Execute Key */

    auto executeHandler =
        new AsyncCallbackJsonWebHandler(
            "/api/key",
            Api::executeKey);

    server.addHandler(executeHandler);

    /* Add Key */

    auto addHandler =
        new AsyncCallbackJsonWebHandler(
            "/api/key/add",
            Api::addKey);

    server.addHandler(addHandler);

    /* Edit Key */

    auto editHandler =
        new AsyncCallbackJsonWebHandler(
            "/api/key/edit",
            Api::editKey);

    editHandler->setMethod(HTTP_PUT);

    server.addHandler(editHandler);

    /* Delete Key */

    auto deleteHandler =
        new AsyncCallbackJsonWebHandler(
            "/api/key/delete",
            Api::deleteKey);

    deleteHandler->setMethod(HTTP_DELETE);

    server.addHandler(deleteHandler);

    /* 404 */

    server.onNotFound([](AsyncWebServerRequest *request)
    {
        request->send(404, "application/json",
                      "{\"success\":false,\"message\":\"Not Found\"}");
    });
}
