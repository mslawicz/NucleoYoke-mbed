/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "Console.h"
#include "FlightControl.h"
#include "Statistics.h"
#include "RotaryEncoder.h"  //XXX
#include "Pushbutton.h" //XXX
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

const uint32_t FlightControlFrequency = 100;    // [Hz]
constexpr uint32_t FlightControlPeriod = 1000 / FlightControlFrequency;     // flight control period [ms]

//XXX pushbutton callback test
void pushbuttonCallback(int level);

// Create a queue of flight control events (RGB LEDs)
EventQueue flightControlQueue;

// Create a thread that'll run the flight control event queue's dispatch function
Thread flightControlQueueDispatchThread(osPriority_t::osPriorityBelowNormal4, OS_STACK_SIZE, nullptr, "flight control");

// Create a queue of pushbuttons and encoders events
EventQueue userInputQueue;

// Create a thread that'll run the user input queue's dispatch function
Thread userInputQueueDispatchThread(osPriority_t::osPriorityBelowNormal6, OS_STACK_SIZE, nullptr, "user input");

// WS2812 RGB LED daisy chain object
WS2812 RGBLeds(PB_15, PB_13, 11);

// Create Console object and its thread
Console console;
Thread consoleThread(osPriority_t::osPriorityLow4, OS_STACK_SIZE, nullptr, "console");

// Create queue of display events
EventQueue displayQueue;
// Create a thread that'll run the display event queue's dispatch function with low priority
Thread displayQueueDispatchThread(osPriority_t::osPriorityBelowNormal, OS_STACK_SIZE, nullptr, "display");
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

    // Start the flight control event queue's dispatch thread
    flightControlQueueDispatchThread.start(callback(&flightControlQueue, &EventQueue::dispatch_forever));

    // Start the user input event queue's dispatch thread
    userInputQueueDispatchThread.start(callback(&userInputQueue, &EventQueue::dispatch_forever));

    // register console commands
    console.registerCommand("h", "help (display command list)", callback(&console, &Console::displayHelp));
    console.registerCommand("lt", "list threads", callback(listThreads));
    console.registerCommand("sd", "display simulator data", callback(&flightControl, &FlightControl::displaySimulatorData));
    console.registerCommand("tv", "display tensometer values", callback(&flightControl, &FlightControl::displayTensometerValues));

    // start Console thread
    consoleThread.start(callback(&console, &Console::handler));

    // Start the display queue's dispatch thread
    displayQueueDispatchThread.start(callback(&displayQueue, &EventQueue::dispatch_forever));

    // initialize display
    display.init();

    display.setFont(FontTahoma16b);
    display.print(2, 0, "Nucleo Yoke");
    display.update();

    // update RGB indicators
    flightControlQueue.call(callback(&RGBLeds, &WS2812::update));

    // display control mode
    flightControl.changeControlMode();

    //XXX test of pushbutton
    Pushbutton encoderButton(PD_3, userInputQueue, pushbuttonCallback);

    uint32_t loopCounter = 0;
    while (true)
    {
        systemLed = (++loopCounter % FlightControlFrequency) < (FlightControlFrequency >> 3);
        flightControl.handler();
        ThisThread::sleep_for(FlightControlPeriod);

        if(loopCounter % FlightControlFrequency == 0)
        {
            //XXX display test
            display.setFont(FontTahoma11);
            display.print(80, 50, std::to_string(loopCounter / FlightControlFrequency) + "  ");
            display.update();
        }
    }
}

/* stubs needed for linker */
extern "C"
{
  int _getpid(){ return -1;}
  int _kill(int pid, int sig){ return -1; }
}

//XXX pushbutton callback test
void pushbuttonCallback(int level)
{
    if(level == 0)
    {
        printf("PB pressed\r\n");
        // pushbutton pressed
        flightControl.changeControlMode(1);
    }
}
