/*
 * FlightControl.h
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_FLIGHTCONTROL_H_
#define SOURCE_FLIGHTCONTROL_H_

#include "mbed.h"
#include "drivers/USBHID.h"

class FlightControl
{
public:
    FlightControl(void);
    void handler(void);
    void connect(void);
private:
    DigitalOut testSignal;   //XXX
    USBHID* pConnection;    // pointer to USB HID object
    static const uint8_t HIDBufferLength = 64;
    static const uint16_t USB_VID = 0x0483;
    static const uint16_t USB_PID = 0x5750;
    static const uint16_t USB_VER = 0x0002;
};

#endif /* SOURCE_FLIGHTCONTROL_H_ */
