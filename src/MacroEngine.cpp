#include "MacroEngine.h"



MacroEngine::MacroEngine(CommandTable *table)
{
    commandTable = table;
}



void MacroEngine::run(String script)
{

    int start = 0;


    while(start < script.length())
    {

        int end = script.indexOf('\n', start);



        if(end == -1)
            end = script.length();



        String line = script.substring(start, end);



        line.trim();



        if(line.length() > 0)
        {
            commandTable->execute(line);
        }



        start = end + 1;


    }

}
