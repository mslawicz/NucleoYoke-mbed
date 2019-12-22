/*
 * Console.cpp
 *
 *  Created on: 22.12.2019
 *      Author: Marcin
 */

#include "Console.h"
#include "mbed.h"

Console::Console()
{
    // TODO Auto-generated constructor stub

}

/*
 * Console handler to be run in a separate thread
 */
void Console::handler(void)
{
    // start console execution with a delay
    ThisThread::sleep_for(500);

    int ch;
    while(true)
    {
        std::string inputLine;
        printf("\r>");
        fflush(stdout);

        do
        {
            ch = getchar();
            switch(ch)
            {
            case 8:
            case 127:
                if(!inputLine.empty())
                {
                    putchar(static_cast<int>(KeyCode::Backspace));
                    putchar(' ');
                    putchar(static_cast<int>(KeyCode::Backspace));
                    fflush(stdout);
                    inputLine.pop_back();
                }
                break;
            default:
                if((ch >= 32) && (ch < 127))
                {
                    inputLine.push_back(static_cast<char>(ch));
                    putchar(ch);
                    fflush(stdout);
                }
                break;
            }
        } while(ch != (int)KeyCode::LF);

        commandElements.clear();
        size_t currentPosition = 0;
        size_t nextSpacePosition;
        do
        {
            nextSpacePosition = inputLine.find(' ', currentPosition);
            auto word = inputLine.substr(currentPosition, nextSpacePosition - currentPosition);
            currentPosition = nextSpacePosition + 1;
            if(!word.empty())
            {
                commandElements.push_back(word);
            }
        } while(nextSpacePosition != std::string::npos);

        printf("\r\n");
        executeCommand();
    }
}

/*
 * register new command in the Console command map
 */
void Console::registerCommand(std::string command, std::string helpText,
        Callback<void(CommandVector)> commandCallback)
{
    commands.emplace(command, CommandContainer{helpText, commandCallback});
}

/*
 * executes console command
 */
void Console::executeCommand(void)
{
    if((!commandElements.empty()) &&
       (!commandElements[0].empty()))
    {
        // command string is given
        auto commandIterator = commands.find(commandElements[0]);
        if(commandIterator != commands.end())
        {
            // this command has been registered - execute it
            commandIterator->second.second(commandElements);
        }
        else
        {
            // unknown command
            printf("unknown command: %s\r\n", commandElements[0].c_str());
        }
    }
}
