#ifndef MACRO_ENGINE_H
#define MACRO_ENGINE_H

#include <Arduino.h>
#include "CommandTable.h"


class MacroEngine
{

private:

    CommandTable *commandTable;


public:

    MacroEngine(CommandTable *table);

    void run(String script);

};


#endif
