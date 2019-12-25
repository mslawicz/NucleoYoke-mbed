/*
 * Display.cpp
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#include "Display.h"

Display::Display(EventQueue& eventQueue) :
    eventQueue(eventQueue)
{

}

/*
 * initialize display
 */
void Display::init(void)
{
    eventQueue.call(callback(&controller, &SH1106::init));
}
