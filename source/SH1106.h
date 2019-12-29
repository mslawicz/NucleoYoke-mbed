/*
 * SH1106.h
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_SH1106_H_
#define SOURCE_SH1106_H_

#include "mbed.h"
#include <vector>

class SH1106
{
public:
    SH1106(PinName dataPin, PinName clkPin, PinName resetPin, PinName cdPin, PinName csPin);
    void init(void);
private:
    void write(uint8_t* data, int length, bool command = false);
    void write(std::vector<uint8_t>data, bool command = false) { write(&data[0], data.size(), command); }
    SPI interface;
    DigitalOut resetSignal;
    DigitalOut cdSignal;
    DigitalOut csSignal;
    const std::vector<uint8_t> SH1106InitData
    {
        0x32,   //DC voltage output value
        0x40,   //display line for COM0 = 0
        0x81,   //contrast
        0x80,
        0xA1,   //segment left rotation
        0xA4,   //display in normal mode
        0xA6,   //display normal indication
        0xAD,   //DC pump on
        0x8B,
        0xC8    //scan from N-1 to 0
    };
};

#endif /* SOURCE_SH1106_H_ */
