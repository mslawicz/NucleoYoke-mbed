/*
 * FlightControl.h
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_FLIGHTCONTROL_H_
#define SOURCE_FLIGHTCONTROL_H_

#include "mbed.h"

class FlightControl
{
public:
    FlightControl(void);
    void handler(void);
private:
    DigitalOut testSignal;   //XXX
};

#endif /* SOURCE_FLIGHTCONTROL_H_ */
