/*
 * FlightControl.cpp
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#include "FlightControl.h"

FlightControl::FlightControl(void) :
    testSignal(PC_8)
{
    // TODO Auto-generated constructor stub

}

/*
 * handler to be called periodically
 * nominal call frequency 80 Hz
 */
void FlightControl::handler(void)
{
    testSignal = !testSignal;
}


