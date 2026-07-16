#include "Api.h"

#include "MacroStorage.h"
#include "MacroManager.h"

void Api::sendSuccess(AsyncWebServerRequest *request)
{
    JsonDocument doc;

    doc["success"] = true;

    String response;
    serializeJson(doc, response);

    request->send(200, "application/json", response);
}

void Api::sendError(AsyncWebServerRequest *request,
                    const char *message,
                    uint16_t code)
{
    JsonDocument doc;

    doc["success"] = false;
    doc["message"] = message;

    String response;
    serializeJson(doc, response);

    request->send(code, "application/json", response);
}

void Api::getKeys(AsyncWebServerRequest *request)
{
    JsonDocument doc;
    JsonArray array = doc.to<JsonArray>();

    MacroStorage::instance().toJson(array);

    String response;
    serializeJson(doc, response);

    request->send(200, "application/json", response);
}

void Api::executeKey(AsyncWebServerRequest *request,
                     JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();

    if (!obj["id"].is<uint16_t>())
    {
        sendError(request, "Invalid id");
        return;
    }

    uint16_t id = obj["id"];

    if (!MacroManager::instance().execute(id))
    {
        sendError(request, "Key not found", 404);
        return;
    }

    sendSuccess(request);
}

void Api::addKey(AsyncWebServerRequest *request,
                 JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();

    if (!MacroStorage::instance().add(obj))
    {
        sendError(request, "Cannot add key");
        return;
    }

    sendSuccess(request);
}

void Api::editKey(AsyncWebServerRequest *request,
                  JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();

    if (!MacroStorage::instance().update(obj))
    {
        sendError(request, "Cannot update key");
        return;
    }

    sendSuccess(request);
}

void Api::deleteKey(AsyncWebServerRequest *request,
                    JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();

    if (!obj["id"].is<uint16_t>())
    {
        sendError(request, "Invalid id");
        return;
    }

    if (!MacroStorage::instance().remove(obj["id"]))
    {
        sendError(request, "Key not found", 404);
        return;
    }

    sendSuccess(request);
}
