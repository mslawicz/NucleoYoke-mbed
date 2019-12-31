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
    RotaryEncoder(PinName clockPin, PinName directionPin);
private:
    void fallingEdgeHandler(void);
    InterruptIn clockSignal;
    DigitalIn directionSignal;
    Timer edgeTime;
};

#endif /* SOURCE_ROTARYENCODER_H_ */
