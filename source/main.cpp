/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "Console.h"
#include "FlightControl.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

const uint32_t FlightControlFrequency = 100;    // [Hz]
constexpr uint32_t FlightControlPeriod = 1000 / FlightControlFrequency;     // flight control period [ms]

// Create a queue of events
EventQueue eventQueue;

// Create a thread that'll run the event queue's dispatch function
Thread eventQueueDispatchThread;

// Create Console object and its thread
Console console;
Thread consoleThread(osPriority_t::osPriorityBelowNormal);

// create main flight control object
FlightControl flightControl;

// WS2812 RGB LED daisy chain object
WS2812 RGBLeds(PB_15, PB_13, 11);

int main()
{
    debug("\r\nmain program start\r\n");
    printf("Nucleo Yoke v2\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    // connect to simulator
    flightControl.connect();

    // Start the event queue's dispatch thread
    eventQueueDispatchThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

    // start Console thread
    consoleThread.start(callback(&console, &Console::handler));

    printf("main loop start\r\n"); //XXX
    uint32_t loopCounter = 0;
    while (true)
    {
        systemLed = (++loopCounter % FlightControlFrequency) < (FlightControlFrequency >> 3);
        flightControl.handler();
        ThisThread::sleep_for(FlightControlPeriod);

        //XXX test on putc / getc
        if((loopCounter % FlightControlFrequency) == 0)
        {
            putchar('.');
            fflush(stdout);
        }
    }
}

/* stubs needed for linker */
extern "C"
{
  int _getpid(){ return -1;}
  int _kill(int pid, int sig){ return -1; }
}
