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

    DigitalOut testLed(LED2);   //XXX
    // start USB HID device in a disconnected state
    USBHID HID(false, 64, 64, 0x0483, 0x5750, 0x0002);
    testLed = 1;
    HID.connect();  //non-blocking !!!
    testLed = 0;
    HID_REPORT inputReport = {.length = 64, .data = {0}};
    HID_REPORT outputReport = {.length = 64, .data = {0}};

    while (true)
    {
        systemLed = !systemLed;
        thread_sleep_for(BLINKING_RATE_MS);

        if(HID.read_nb(&inputReport))
        {
            uint8_t i = 0;
            for(auto byte : inputReport.data)
            {
                outputReport.data[i++] = byte+1;
            }
            // non-blocking is safe even when device is not ready
            HID.send_nb(&outputReport);
        }
    }
}

