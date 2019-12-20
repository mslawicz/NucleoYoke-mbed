/*
 * FlightControl.cpp
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#include "FlightControl.h"
#include "platform/mbed_debug.h"

FlightControl::FlightControl(void) :
    testSignal(PC_8)
{
    pConnection = nullptr;
}

/*
 * handler to be called periodically
 * nominal call frequency 80 Hz
 */
void FlightControl::handler(void)
{
    testSignal = !testSignal;   //XXX
    bool newDataReceived = false;

    // check data received from simulator
    if((pConnection != nullptr) &&
       (pConnection->read_nb(&inputReport)))
    {
        // new data from simulator has been received
        newDataReceived = true;
        // parse data here
    }

    // send output report to simulator
    if(newDataReceived)
    {
        // fill output report data here
        pConnection->send_nb(&outputReport);
    }
}

/*
 * connect to simulator using USB HID connection
 */
void FlightControl::connect(void)
{
    // create and start USB HID device object in a disconnected state
    pConnection = new USBHID(false, HIDBufferLength, HIDBufferLength, USB_VID, USB_PID, USB_VER);
    // start connection process
    pConnection->connect();
    debug("Connecting to PC using USB HID (VID=%#06X PID=%#06X ver=%d)\r\n", USB_VID, USB_PID, USB_VER);
}
