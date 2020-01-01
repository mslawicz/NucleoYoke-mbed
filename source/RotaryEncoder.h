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
    RotaryEncoder(PinName clockPin, PinName directionPin, EventQueue& eventQueue, Callback<void(bool)> onPulse);
private:
    void fallingEdgeHandler(void) { debouncer.attach(callback(this, &RotaryEncoder::pulseHandler), DebounceTime); }
    void pulseHandler(void);
    InterruptIn clockSignal;
    DigitalIn directionSignal;
    EventQueue& eventQueue;     // event queue for deferring onPulse callback
    Callback<void(bool)> onPulse;
    Timeout debouncer;
    const float DebounceTime = 0.005f;   // required stable clock time [s]
};

#endif /* SOURCE_ROTARYENCODER_H_ */
