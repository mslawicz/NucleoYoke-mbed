/*
 * Console.cpp
 *
 *  Created on: 22.12.2019
 *      Author: Marcin
 */

#include "Console.h"
#include "mbed.h"
#include <vector>

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
        inputLine.clear();
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

        std::vector<std::string> words;
        size_t currentPosition = 0;
        size_t nextSpacePosition;
        do
        {
            nextSpacePosition = inputLine.find(' ', currentPosition);
            auto word = inputLine.substr(currentPosition, nextSpacePosition - currentPosition);
            currentPosition = nextSpacePosition + 1;
            if(!word.empty())
            {
                words.push_back(word);
            }
        } while(nextSpacePosition != std::string::npos);

        // interpret command here
    }
}
