/*
 * Display.cpp
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#include "Display.h"

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

/*
 * displays character on the screen
 * ch - ascii code
 * X,Y - upper left corner of character placement
 * font - font array from fonts.h
 * inverted - clears pixels if true
 * upToX - if >0, stops at X==upToX
 */
void Display::putChar(uint8_t X, uint8_t Y, uint8_t ch, const uint8_t* font,
        bool inverted, uint8_t upToX)
{
    eventQueue.call(callback(&controller, &SH1106::putChar), X, Y, ch);
}
