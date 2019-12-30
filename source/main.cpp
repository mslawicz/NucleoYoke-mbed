/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "Console.h"
#include "Display.h"
#include "FlightControl.h"
#include "Statistics.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

const uint32_t FlightControlFrequency = 100;    // [Hz]
constexpr uint32_t FlightControlPeriod = 1000 / FlightControlFrequency;     // flight control period [ms]

// Create a queue of flight control events
EventQueue flightControlQueue;

// Create a thread that'll run the event queue's dispatch function
Thread flightControlQueueDispatchThread(osPriority_t::osPriorityBelowNormal4, OS_STACK_SIZE, nullptr, "events");

// WS2812 RGB LED daisy chain object
WS2812 RGBLeds(PB_15, PB_13, 11);

// Create Console object and its thread
Console console;
Thread consoleThread(osPriority_t::osPriorityBelowNormal, OS_STACK_SIZE, nullptr, "console");

// Create queue of display events
EventQueue displayQueue;
// Create a thread that'll run the display event queue's dispatch function with low priority
Thread displayQueueDispatchThread(osPriority_t::osPriorityLow4, OS_STACK_SIZE, nullptr, "display");
// Create display object
Display display(displayQueue);

// create main flight control object
FlightControl flightControl(flightControlQueue, RGBLeds);

int main()
{
    debug("\r\nmain program start\r\n");
    printf("Nucleo Yoke v2\r\n");
    printf("type command 'h' for help\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    // connect to simulator
    flightControl.connect();

    // Start the event queue's dispatch thread
    flightControlQueueDispatchThread.start(callback(&flightControlQueue, &EventQueue::dispatch_forever));

    // register console commands
    console.registerCommand("h", "help (display command list)", callback(&console, &Console::displayHelp));
    console.registerCommand("ls", "list threads", callback(listThreads));
    console.registerCommand("sd", "display simulator data", callback(&flightControl, &FlightControl::displaySimulatorData));

    // start Console thread
    consoleThread.start(callback(&console, &Console::handler));

    // Start the display queue's dispatch thread
    displayQueueDispatchThread.start(callback(&displayQueue, &EventQueue::dispatch_forever));

    // initialize display
    display.init();

    //XXX test of display
    display.test();

    uint32_t loopCounter = 0;
    while (true)
    {
        systemLed = (++loopCounter % FlightControlFrequency) < (FlightControlFrequency >> 3);
        flightControl.handler();
        ThisThread::sleep_for(FlightControlPeriod);
    }
}

/* stubs needed for linker */
extern "C"
{
  int _getpid(){ return -1;}
  int _kill(int pid, int sig){ return -1; }
}
