/*
 * Display.cpp
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#include "Display.h"
#include "fonts.h"

Display::Display(EventQueue& eventQueue) :
    controller(PE_14, PE_12, PE_15, PE_13, PF_13),
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

/*
 * call display test function
 */
void Display::test(void)
{
    uint8_t argument = 30;
    eventQueue.call(callback(&controller, &SH1106::test), argument);
}
