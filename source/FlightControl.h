/*
 * FlightControl.h
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_FLIGHTCONTROL_H_
#define SOURCE_FLIGHTCONTROL_H_

//#include "mbed.h"

class FlightControl
{
public:
    FlightControl();
    void setTicker(void);
private:
    void handler(void);
    //Ticker periodicCall;
    //static constexpr float LoopPeriod = 1.0f / 80.0f;      // loop period [s]
};

#endif /* SOURCE_FLIGHTCONTROL_H_ */
