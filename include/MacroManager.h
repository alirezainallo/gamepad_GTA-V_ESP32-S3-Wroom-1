#pragma once

#include <Arduino.h>

class MacroManager
{
public:

    static MacroManager& instance();

    bool begin();

    bool execute(uint16_t id);

private:

    MacroManager() = default;

    bool executeCommand(const String &command,
                        bool tabBefore,
                        bool enterAfter);
};
