#pragma once

#include <Arduino.h>
#include <vector>

#include <ArduinoJson.h>

struct MacroKey
{
    uint16_t id;

    String name;

    String command;

    bool tabBefore;

    bool enterAfter;
};

class MacroStorage
{
public:

    static MacroStorage& instance();

    bool begin();

    bool load();

    bool save();

    bool add(const JsonObject &obj);

    bool update(const JsonObject &obj);

    bool remove(uint16_t id);

    MacroKey* find(uint16_t id);

    const std::vector<MacroKey>& getKeys() const;

    void toJson(JsonArray array) const;

private:

    MacroStorage() = default;

    std::vector<MacroKey> _keys;
};
