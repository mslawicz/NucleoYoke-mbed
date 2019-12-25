/*
 * Display.h
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_DISPLAY_H_
#define SOURCE_DISPLAY_H_

#include "SH1106.h"

class Display
{
public:
    Display();
private:
    SH1106 controller;
};

#endif /* SOURCE_DISPLAY_H_ */
