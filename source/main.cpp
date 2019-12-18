/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS    500

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    while (true)
    {
        systemLed = !systemLed;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
