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
    onPulse(onPulse),
    testPin(PB_8)   //XXX
{
    clockSignal.fall(callback(this, &RotaryEncoder::fallingEdgeHandler));
    testPin = 0; //XXX
}

/*
 * clock signal falling edge interrupt handler
 */
void RotaryEncoder::fallingEdgeHandler(void)
{
    testPin = 1;
    debouncer.attach(callback(this, &RotaryEncoder::pulseHandler), DebounceTime);
    testPin = 0;
}

/*
 * pulse timeout handler
 */
void RotaryEncoder::pulseHandler(void)
{
    testPin = 1;
    if(onPulse && (clockSignal.read() == 0))
    {
        // stable clock in level 0, call onPulse event in main context
        eventQueue.call(onPulse, directionSignal != 0);
    }
    testPin = 0;
}
