/*
 * WS2812.h
 *
 *  Created on: 21.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_WS2812_H_
#define SOURCE_WS2812_H_

#include "mbed.h"
#include <vector>

class WS2812
{
public:
    WS2812(PinName dataPin, PinName clkPin, uint16_t numberOfDevices);
private:
    SPI interface;
    uint16_t numberOfDevices;
    uint32_t* pRGBData;
};

#endif /* SOURCE_WS2812_H_ */
