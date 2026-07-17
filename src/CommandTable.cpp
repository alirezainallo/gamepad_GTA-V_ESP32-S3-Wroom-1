#include "CommandTable.h"


KeyboardActions *CommandTable::instance = nullptr;



//===============================
// Command Functions
//===============================

void CommandTable::cmdType(String args)
{
    Serial.printf("[CommandTable] cmdType:\'%s\'\n", args);
    instance->typeText(args);
}



void CommandTable::cmdDelay(String args)
{
    Serial.printf("[CommandTable] cmdDelay:\'%s\'\n", args);
    delay(args.toInt());
}



void CommandTable::cmdKey(String args)
{
    Serial.printf("[CommandTable] cmdKey:\'%s\'\n", args);
    instance->pressKey(args);
}



//===============================
// Command List
//===============================

Command commands[] =
{

    {
        "type",
        CommandTable::cmdType
    },


    {
        "delay",
        CommandTable::cmdDelay
    },


    {
        "key",
        CommandTable::cmdKey
    }

};



const uint8_t COMMAND_COUNT =
sizeof(commands) / sizeof(Command);



//===============================
// Constructor
//===============================

CommandTable::CommandTable(KeyboardActions *actions)
{
    keyboardActions = actions;

    instance = keyboardActions;
}



//===============================
// Execute command
//===============================

void CommandTable::execute(String command)
{

    command.trim();


    if(command.length() == 0)
        return;



    int separator = command.indexOf(' ');



    String cmd;
    String args;



    if(separator == -1)
    {
        cmd = command;
        args = "";
    }
    else
    {
        cmd = command.substring(0, separator);
        args = command.substring(separator + 1);
    }



    cmd.toLowerCase();



    for(uint8_t i = 0; i < COMMAND_COUNT; i++)
    {

        if(cmd == commands[i].name)
        {
            commands[i].function(args);
            return;
        }

    }



    // If command is not found,
    // treat it as a keyboard key
    Serial.printf("cmd: %s, not found\n", cmd.c_str());
    keyboardActions->pressKey(cmd);

}