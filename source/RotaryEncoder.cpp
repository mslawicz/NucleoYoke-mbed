/*
 * RotaryEncoder.cpp
 *
 *  Created on: 31.12.2019
 *      Author: Marcin
 */

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(PinName clockPin, PinName directionPin) :
    clockSignal(clockPin),
    directionSignal(directionPin)
{
    edgeTime.start();
    clockSignal.fall(callback(this, &RotaryEncoder::fallingEdgeHandler));
}

/*
 * clock signal falling edge interrupt handler
 */
void RotaryEncoder::fallingEdgeHandler(void)
{
    int direction = directionSignal;
    edgeTime.reset();
}
