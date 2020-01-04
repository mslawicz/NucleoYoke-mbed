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

class Display;
extern Display display;

class Display
{
public:
    Display(EventQueue& eventQueue);
    void init(void);
    void test(void);
    void update(void) { printf("eventQueue.call=%d, %p, %p\r\n", eventQueue.call(callback(&controller, &SH1106::update)), &controller, &SH1106::update); }
    void setFont(const uint8_t* newFont, bool newInvertion = false, uint8_t newXLimit = 0);
    void putChar(uint8_t X, uint8_t Y, uint8_t ch) { eventQueue.call(callback(&controller, &SH1106::putChar), X, Y, ch); } // displays character on the screen
    void print(uint8_t X, uint8_t Y, std::string text)  { eventQueue.call(callback(&controller, &SH1106::print), X, Y, text); } // displays string on the screen
private:
    SH1106 controller;
    EventQueue& eventQueue;
};

#endif /* SOURCE_DISPLAY_H_ */
