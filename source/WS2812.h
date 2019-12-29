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

enum class WS2812Color : uint32_t
{
    off = 0,
    blue = 0x000004,
    red = 0x000400,
    green = 0x040000,
    magenta = 0x000202,
    cyan = 0x020002,
    yellow = 0x020200,
    orange = 0x010300,
    white = 0x020202,
    gray = 0x010101
};

class WS2812
{
public:
    WS2812(PinName dataPin, PinName clkPin, uint16_t numberOfDevices);
    void update(void);
    void setValue(uint8_t deviceIndex, uint32_t value);
private:
    SPI interface;
    uint16_t numberOfDevices;       // number of devices in the chain
    std::vector<uint32_t> RGBData;          // vector of device RGB values
    std::vector<uint8_t> oneWireBuffer;     // vector of pulses being sent to devices
    const uint8_t bitOnePattern = 0b1110;   // pattern of the 1-wire bit '1'
    const uint8_t bitZeroPattern = 0b1000;   // pattern of the 1-wire bit '0'
};

#endif /* SOURCE_WS2812_H_ */
