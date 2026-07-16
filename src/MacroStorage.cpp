#include "MacroStorage.h"

#include <LittleFS.h>

#define MACRO_DB_FILE "/macros.json"

MacroStorage& MacroStorage::instance()
{
    static MacroStorage storage;
    return storage;
}

bool MacroStorage::begin()
{
    return load();
}

bool MacroStorage::load()
{
    _keys.clear();

    if (!LittleFS.exists(MACRO_DB_FILE))
    {
        save();
        return true;
    }

    File file = LittleFS.open(MACRO_DB_FILE, "r");
    if (!file)
        return false;

    JsonDocument doc;

    if (deserializeJson(doc, file))
    {
        file.close();
        return false;
    }

    file.close();

    JsonArray array = doc.as<JsonArray>();

    for (JsonObject obj : array)
    {
        MacroKey key;

        key.id          = obj["id"] | 0;
        key.name        = obj["name"] | "";
        key.command     = obj["command"] | "";
        key.tabBefore   = obj["tabBefore"] | false;
        key.enterAfter  = obj["enterAfter"] | false;

        _keys.push_back(key);
    }

    return true;
}

bool MacroStorage::save()
{
    JsonDocument doc;
    JsonArray array = doc.to<JsonArray>();

    for (const auto &key : _keys)
    {
        JsonObject obj = array.add<JsonObject>();

        obj["id"] = key.id;
        obj["name"] = key.name;
        obj["command"] = key.command;
        obj["tabBefore"] = key.tabBefore;
        obj["enterAfter"] = key.enterAfter;
    }

    File file = LittleFS.open(MACRO_DB_FILE, "w");
    if (!file)
        return false;

    serializeJsonPretty(doc, file);

    file.close();

    return true;
}

bool MacroStorage::add(const JsonObject &obj)
{
    MacroKey key;

    key.id         = obj["id"];
    key.name       = obj["name"].as<String>();
    key.command    = obj["command"].as<String>();
    key.tabBefore  = obj["tabBefore"] | false;
    key.enterAfter = obj["enterAfter"] | false;

    _keys.push_back(key);

    return save();
}

bool MacroStorage::update(const JsonObject &obj)
{
    uint16_t id = obj["id"];

    MacroKey *key = find(id);

    if (key == nullptr)
        return false;

    key->name        = obj["name"].as<String>();
    key->command     = obj["command"].as<String>();
    key->tabBefore   = obj["tabBefore"] | false;
    key->enterAfter  = obj["enterAfter"] | false;

    return save();
}

bool MacroStorage::remove(uint16_t id)
{
    for (auto it = _keys.begin(); it != _keys.end(); ++it)
    {
        if (it->id == id)
        {
            _keys.erase(it);
            return save();
        }
    }

    return false;
}

MacroKey* MacroStorage::find(uint16_t id)
{
    for (auto &key : _keys)
    {
        if (key.id == id)
            return &key;
    }

    return nullptr;
}

const std::vector<MacroKey>& MacroStorage::getKeys() const
{
    return _keys;
}

void MacroStorage::toJson(JsonArray array) const
{
    for (const auto &key : _keys)
    {
        JsonObject obj = array.add<JsonObject>();

        obj["id"] = key.id;
        obj["name"] = key.name;
        obj["command"] = key.command;
        obj["tabBefore"] = key.tabBefore;
        obj["enterAfter"] = key.enterAfter;
    }
}
