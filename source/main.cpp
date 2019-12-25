/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "HX711.h"
#include "Servo.h"  //XXX servo objects should be defined rather in Flight Control
#include "Console.h"
#include "Display.h"
#include "FlightControl.h"
#include "Statistics.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

const uint32_t FlightControlFrequency = 100;    // [Hz]
constexpr uint32_t FlightControlPeriod = 1000 / FlightControlFrequency;     // flight control period [ms]

// Create a queue of events
EventQueue eventQueue;

// Create a thread that'll run the event queue's dispatch function
Thread eventQueueDispatchThread(osPriority_t::osPriorityBelowNormal4, OS_STACK_SIZE, nullptr, "events");

// WS2812 RGB LED daisy chain object
WS2812 RGBLeds(PB_15, PB_13, 11);

// create HX711 tensometer DAC objects
HX711 throttleTensometer(PD_12, PD_13, &eventQueue);

// Create Console object and its thread
Console console;
Thread consoleThread(osPriority_t::osPriorityBelowNormal, OS_STACK_SIZE, nullptr, "console");

// Create display object
Display display;

// create main flight control object
FlightControl flightControl;

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
    eventQueueDispatchThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

    // register console commands
    console.registerCommand("h", "help (display command list)", callback(&console, &Console::displayHelp));
    console.registerCommand("ts", "display thread statistics", callback(displayThreadStatistics));

    // start Console thread
    consoleThread.start(callback(&console, &Console::handler));

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
