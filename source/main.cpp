/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "FlightControl.h"
#include "mbed.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"


const uint32_t SystemLedPeriod = 500;   // [ms]
constexpr float FlightControlPeriod = 1.0f / 80.0f;     // flight control period [s]

// create main flight control object
FlightControl flightControl;

int main()
{
    debug("main program start\r\n");
    printf("Nucleo Yoke v2\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    // connect to simulator
    flightControl.connect();
    // set periodic Flight Control call (80 times per second)
    Ticker periodicFlightControlCall;
    periodicFlightControlCall.attach(callback(&flightControl, &FlightControl::handler), FlightControlPeriod);

    while (true)
    {
        systemLed = !systemLed;
        thread_sleep_for(SystemLedPeriod);
    }
}

