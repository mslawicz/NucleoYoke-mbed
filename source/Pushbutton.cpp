/*
 * Pushbutton.cpp
 *
 *  Created on: 01.01.2020
 *      Author: Marcin
 */

#include "Pushbutton.h"

Pushbutton::Pushbutton(PinName switchPin, EventQueue& eventQueue, Callback<void(int)> onSwitch) :
    switchSignal(switchPin),
    eventQueue(eventQueue),
    onSwitch(onSwitch)
{
    switchSignal.fall(callback(this, &Pushbutton::edgeHandler));
    switchSignal.rise(callback(this, &Pushbutton::edgeHandler));
}

/*
 * called after switched signal is stable
 */
void Pushbutton::switchHandler(void)
{
    if(onSwitch)
    {
        eventQueue.call(onSwitch, switchSignal.read());
    }
}
