/*
 * FlightControl.cpp
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#include "FlightControl.h"
#include "platform/mbed_debug.h"

FlightControl::FlightControl(void) :
    simulatorDataIndicator(LED2)      // blue LED
{
    pConnection = nullptr;
    simulatorDataIndicator = 0;
    simulatorDataActive = false;
}

/*
 * handler to be called periodically
 * nominal call period 10 ms
 */
void FlightControl::handler(void)
{
    bool newDataReceived = false;

    // check data received from simulator
    if((pConnection != nullptr) &&
       (pConnection->read_nb(&inputReport)))
    {
        // new data from simulator has been received
        newDataReceived = true;
        simulatorDataIndicator = 1;
        simulatorDataActive = true;
        simulatorDataTimeout.attach(callback(this, &FlightControl::markSimulatorDataInactive), 0.2f);
        parseReceivedData();
    }

    // send output report to simulator
    if(newDataReceived)
    {
        //XXX test of transmission
        for(uint8_t k = 0; k < inputReport.data[0]; k++)
        {
            printf("%u,", inputReport.data[k+1]);
            outputReport.data[k+1] = inputReport.data[k+1] + 1;
        }
        outputReport.data[0] = inputReport.data[0];
        printf("\r\n");

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

/*
 * mark simulator data is not up to date and is inactive now
 * it is called after timeout elapsed after the last data reception
 */
void FlightControl::markSimulatorDataInactive(void)
{
    simulatorDataActive = false;
    simulatorDataIndicator = 0;
}

/*
 * parse received simulator data into simulator data structure
 */
void FlightControl::parseReceivedData(void)
{
    simulatorData.booleanFlags = *(inputReport.data+1);
    simulatorData.gearDeflection[0] = ((*(inputReport.data+3)) >> 0) & 0x03;
    simulatorData.gearDeflection[1] = ((*(inputReport.data+3)) >> 2) & 0x03;
    simulatorData.gearDeflection[2] = ((*(inputReport.data+3)) >> 4) & 0x03;
    simulatorData.flapsDeflection = *reinterpret_cast<float*>(inputReport.data+4);
    simulatorData.totalPitch = *reinterpret_cast<float*>(inputReport.data+8);
    simulatorData.totalRoll = *reinterpret_cast<float*>(inputReport.data+12);
    simulatorData.totalYaw = *reinterpret_cast<float*>(inputReport.data+16);
    simulatorData.throttle = *reinterpret_cast<float*>(inputReport.data+20);
    simulatorData.airSpeed = *reinterpret_cast<float*>(inputReport.data+24);
    simulatorData.propellerSpeed = *reinterpret_cast<float*>(inputReport.data+28);
}
