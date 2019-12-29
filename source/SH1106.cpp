/*
 * SH1106.cpp
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#include "SH1106.h"

SH1106::SH1106(PinName dataPin, PinName clkPin, PinName resetPin, PinName cdPin, PinName csPin) :
    interface(dataPin, NC, clkPin),
    resetSignal(PE_15),
    cdSignal(cdPin),
    csSignal(csPin)
{
    csSignal = 1;
}

/*
 * initialization of SH1106 controller
 */
void SH1106::init(void)
{
    resetSignal = 0;
    resetSignal = 1;
    // wait after reset
    ThisThread::sleep_for(1);
    // send initialization data
    write(SH1106InitData, true);
}

/*
 * send command/data to display controller
 */
void SH1106::write(const char* data, int length, bool command)
{
    cdSignal = command ? 0 : 1;
    csSignal = 0;
    interface.write(data, length, nullptr, 0);
    csSignal = 1;
}
