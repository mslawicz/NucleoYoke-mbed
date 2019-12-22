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
        ch = getchar();
        printf("%u,", ch);
        fflush(stdout);
    }
}
