/*
 * RotaryEncoder.cpp
 *
 *  Created on: 31.12.2019
 *      Author: Marcin
 */

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(PinName clockPin, PinName directionPin, EventQueue& eventQueue, Callback<void(bool)> onPulse) :
    clockSignal(clockPin),
    directionSignal(directionPin),
    eventQueue(eventQueue),
    onPulse(onPulse)
{
    clockSignal.fall(callback(this, &RotaryEncoder::fallingEdgeHandler));
}

/*
 * pulse timeout handler
 */
void RotaryEncoder::pulseHandler(void)
{
    if(onPulse && (clockSignal.read() == 0))
    {
        // stable clock in level 0, call onPulse event in main context
        eventQueue.call(onPulse, directionSignal != 0);
    }
}
