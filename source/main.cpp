/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "FlightControl.h"
#include "mbed.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

SPI ledRGB(PB_15, PA_12, PB_13);    //XXX
DigitalOut testSignal(PC_8);        //XXX
//uint8_t dataBuffer[] = {0xC0,0xC0,0xC0,0xC0,0xC0,0xFC,0xC0,0xC0,  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFC,0xFC};    //XXX
uint8_t dataBuffer[] = {0x88,0x88,0x88,0x88,  0x88,0x88,0xE8,0x88,  0x88,0x88,0x88,0x88,  0x88,0x88,0x88,0x88,  0x88,0x88,0x88,0x88,  0x88,0x88,0xE8,0x88,
        0x88,0x88,0xE8,0x88,  0x88,0x88,0x88,0x88,  0x88,0x88,0x88,0x88,  0x88,0x88,0x8E,0x88,  0x88,0x88,0x8E,0x88,  0x88,0x88,0x88,0x88};    //XXX
void dummyCallback(void) {} //XXX

const uint32_t FlightControlFrequency = 100;    // [Hz]
constexpr uint32_t FlightControlPeriod = 1000 / FlightControlFrequency;     // flight control period [ms]

// create main flight control object
FlightControl flightControl;

int main()
{
    debug("\r\nmain program start\r\n");
    printf("Nucleo Yoke v2\r\n");

    ledRGB.frequency(4000000);
    ledRGB.format(8, 1);

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    // connect to simulator
    flightControl.connect();

    uint32_t loopCounter = 0;
    while (true)
    {
        systemLed = (++loopCounter % FlightControlFrequency) < (FlightControlFrequency >> 3);
        flightControl.handler();
        thread_sleep_for(FlightControlPeriod);

        // XXX SPI test
        testSignal = 1;
        ledRGB.transfer<uint8_t>(dataBuffer, sizeof(dataBuffer), NULL, 0, NULL, 0);
        //ledRGB.write((const char*)dataBuffer, sizeof(dataBuffer), NULL, 0);
        testSignal = 0;
    }
}

