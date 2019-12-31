/*
 * RotaryEncoder.h
 *
 *  Created on: 31.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_ROTARYENCODER_H_
#define SOURCE_ROTARYENCODER_H_

#include "mbed.h"

class RotaryEncoder
{
public:
    RotaryEncoder(PinName clockPin, PinName directionPin, Callback<void(bool)> onPulse);
private:
    void fallingEdgeHandler(void);
    InterruptIn clockSignal;
    DigitalIn directionSignal;
    Timer edgeTime;
    Callback<void(bool)> onPulse;
    static const int MinimalGap = 20;   // minimal time between falling edges for debouncing
};

#endif /* SOURCE_ROTARYENCODER_H_ */
