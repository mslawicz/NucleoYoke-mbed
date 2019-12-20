/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "FlightControl.h"
#include "mbed.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

const uint32_t FlightControlFrequency = 100;    // [Hz]
constexpr uint32_t FlightControlPeriod = 1000 / FlightControlFrequency;     // flight control period [ms]

// create main flight control object
FlightControl flightControl;

int main()
{
    debug("\r\nmain program start\r\n");
    printf("Nucleo Yoke v2\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    // connect to simulator
    flightControl.connect();

    uint32_t loopCounter = 0;
    while (true)
    {
        systemLed = (++loopCounter % FlightControlFrequency) < 15;
        flightControl.handler();
        thread_sleep_for(FlightControlPeriod);
    }
}

