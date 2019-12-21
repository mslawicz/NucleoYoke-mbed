/*
 * WS2812.cpp
 *
 *  Created on: 21.12.2019
 *      Author: Marcin
 */

#include "WS2812.h"

WS2812::WS2812(PinName dataPin, PinName clkPin, uint16_t numberOfDevices) :
    interface(dataPin, NC, clkPin),
    numberOfDevices(numberOfDevices)
{
    pRGBData = new uint32_t[numberOfDevices];
}

/*
 * update RGB LED devices in the chain
 */
void WS2812::update(void)
{
    static DigitalOut testSignal(PC_9); //XXX
    testSignal = !testSignal;
}
