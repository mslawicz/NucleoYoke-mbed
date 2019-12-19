/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS    500

int main()
{
    debug("main program start\r\n");
    printf("Nucleo Yoke v2\r\n");
    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    while (true)
    {
        systemLed = !systemLed;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
