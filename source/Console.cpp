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
    while(true)
    {
        ThisThread::sleep_for(1500);
        putchar('_');
        fflush(stdout);
    }
}
