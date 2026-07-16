#include "MacroManager.h"

#include "MacroStorage.h"

#include <USB.h>
#include <USBHIDKeyboard.h>

extern USBHIDKeyboard Keyboard;

MacroManager& MacroManager::instance()
{
    static MacroManager manager;
    return manager;
}

bool MacroManager::begin()
{
    return true;
}

bool MacroManager::execute(uint16_t id)
{
    MacroKey* key = MacroStorage::instance().find(id);

    if (key == nullptr)
        return false;

    return executeCommand(
        key->command,
        key->tabBefore,
        key->enterAfter);
}

bool MacroManager::executeCommand(const String& command,
                                  bool tabBefore,
                                  bool enterAfter)
{
    if (tabBefore)
    {
        Keyboard.press(KEY_TAB);
        delay(5);
        Keyboard.releaseAll();
        delay(5);
    }

    Keyboard.print(command);

    if (enterAfter)
    {
        delay(5);
        Keyboard.press(KEY_RETURN);
        delay(5);
        Keyboard.releaseAll();
    }

    return true;
}
