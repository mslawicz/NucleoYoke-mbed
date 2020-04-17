/* Nucleo Yoke program
 * mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "Console.h"
#include "FlightControl.h"
#include "Statistics.h"
#include "Alarm.h"
#include "Pushbutton.h" //XXX
#include "platform/mbed_thread.h"
#include "platform/mbed_debug.h"

//XXX pushbutton callback test
void pushbuttonCallback(int level);

// Initialise the alarm object
Alarm alarm;

// Create a queue for flight control events calls
EventQueue flightControlQueue;

// Create a thread that'll run the flight control event queue's dispatch function
Thread flightControlQueueDispatchThread(osPriority_t::osPriorityBelowNormal4, OS_STACK_SIZE, nullptr, "flight control");

// Create a queue of pushbuttons and encoders events
EventQueue userInputQueue;

// Create a thread that'll run the user input queue's dispatch function
Thread userInputQueueDispatchThread(osPriority_t::osPriorityBelowNormal6, OS_STACK_SIZE, nullptr, "user input");

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
FlightControl flightControl(flightControlQueue);

int main()
{
    debug("\r\nmain program start\r\n");
    printf("Nucleo Yoke v3\r\n");
    printf("type command 'h' for help\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut systemLed(LED1);

    // configure FlightControl object
    flightControl.config();
    // connect to PC
    flightControl.connect();

    // Start the flight control event queue's dispatch thread
    flightControlQueueDispatchThread.start(callback(&flightControlQueue, &EventQueue::dispatch_forever));

    // Start the user input event queue's dispatch thread
    userInputQueueDispatchThread.start(callback(&userInputQueue, &EventQueue::dispatch_forever));

    // register console commands
    console.registerCommand("h", "help (display command list)", callback(&console, &Console::displayHelp));
    console.registerCommand("lt", "list threads", callback(listThreads));
    console.registerCommand("fc", "display Flight Control status", callback(&flightControl, &FlightControl::displayStatus));
    console.registerCommand("da", "display alarms", callback(&alarm, &Alarm::display));
    console.registerCommand("ca", "clear alarms", callback(&alarm, &Alarm::clear));

    // start Console thread
    consoleThread.start(callback(&console, &Console::handler));

    // Start the display queue's dispatch thread
    displayQueueDispatchThread.start(callback(&displayQueue, &EventQueue::dispatch_forever));

    // initialize display
    display.init();

    display.setFont(FontTahoma16b);
    display.print(2, 0, "Nucleo Yoke");
    display.update();

    //XXX test of pushbutton
    Pushbutton encoderButton(PD_3, userInputQueue, pushbuttonCallback);

    while (true)
    {
        // heartbeat in main loop only
        systemLed = !systemLed;
        ThisThread::sleep_for(500);
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
        // pushbutton pressed
    }
}
