/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"
#include "drivers/USBHID.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS    500

int main()
{
    debug("main program start\r\n");
    printf("Nucleo Yoke v2\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    USBHID HID(true, 64, 64, 0x0483, 0x5750, 0x0002);
    HID_REPORT outputReport = {.length = 64, .data = {1, 2, 3}};

    while (true)
    {
        systemLed = !systemLed;
        thread_sleep_for(BLINKING_RATE_MS);

        HID.send(&outputReport);
    }
}
