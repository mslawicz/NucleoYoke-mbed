/*
 * Pushbutton.h
 *
 *  Created on: 01.01.2020
 *      Author: Marcin
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "mbed.h"

class Pushbutton
{
public:
    Pushbutton(PinName switchPin, EventQueue& eventQueue, Callback<void(int)> onSwitch);
private:
    void edgeHandler(void) { debouncer.attach(callback(this, &Pushbutton::switchHandler), DebounceTime); }
    void switchHandler(void);
    InterruptIn switchSignal;
    EventQueue& eventQueue;     // event queue for deferring onSwitch callback
    Callback<void(int)> onSwitch;
    Timeout debouncer;
    const float DebounceTime = 0.005f;   // required stable level time [s] before onSwitch call is placed in the queue
};

#endif /* PUSHBUTTON_H_ */
