/*
 * RotaryEncoder.cpp
 *
 *  Created on: 31.12.2019
 *      Author: Marcin
 */

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(PinName clockPin, PinName directionPin, Callback<void(bool)> onPulse) :
    clockSignal(clockPin),
    directionSignal(directionPin),
    onPulse(onPulse)
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
    if(onPulse && (edgeTime.read_ms() > MinimalGap))
    {
        onPulse(direction != 0);
    }
    edgeTime.reset();
}
