/*
 * Display.h
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_DISPLAY_H_
#define SOURCE_DISPLAY_H_

#include "mbed.h"
#include "SH1106.h"

class Display
{
public:
    Display(EventQueue& eventQueue);
    void init(void);
    void test(void);
    void update(void) { eventQueue.call(callback(&controller, &SH1106::update)); }
    void putChar(uint8_t X, uint8_t Y, uint8_t ch, const uint8_t* font, bool inverted = false, uint8_t upToX = 0);
private:
    SH1106 controller;
    EventQueue& eventQueue;
};

#endif /* SOURCE_DISPLAY_H_ */
