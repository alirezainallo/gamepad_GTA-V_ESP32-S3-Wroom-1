#ifndef COMMAND_TABLE_H
#define COMMAND_TABLE_H

#include <Arduino.h>
#include "KeyboardActions.h"


typedef void (*CommandFunction)(String args);


struct Command
{
    const char *name;
    CommandFunction function;
};


class CommandTable
{
private:

    KeyboardActions *keyboardActions;
    
    static KeyboardActions *instance;
    
    
    public:
    
    static void cmdType(String args);
    static void cmdDelay(String args);
    static void cmdKey(String args);
    
    CommandTable(KeyboardActions *actions);

    void execute(String command);

};


#endif
