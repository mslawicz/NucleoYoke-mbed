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
private:
    SH1106 controller;
    EventQueue& eventQueue;
};

#endif /* SOURCE_DISPLAY_H_ */
