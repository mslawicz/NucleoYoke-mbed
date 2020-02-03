/*
 * FlightControl.h
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_FLIGHTCONTROL_H_
#define SOURCE_FLIGHTCONTROL_H_

#include "Console.h"
#include "Display.h"
#include "mbed.h"
#include "drivers/USBHID.h"


// data received from simulator in incoming USB report
struct SimulatorData
{
    /*
     * bits of boolean flags:
     * 0 any gear is retractable
     * 1 stick shaker is on
     * 2 reverser is deployed
     */
    uint16_t booleanFlags;
    uint8_t gearDeflection[3]; // gear deflection state: 0-up, 1-on the way, 2-down; array of 3 gear units
    float flapsDeflection;  // flaps deflection ratio 0..1
    float totalPitch;   // total pitch control input (sum of user yoke plus autopilot servo plus artificial stability) <-1.0f .. 1.0f>
    float totalRoll;    // total roll control input (sum of user yoke plus autopilot servo plus artificial stability) <-1.0f .. 1.0f>
    float totalYaw;     // total yaw control input (sum of user yoke plus autopilot servo plus artificial stability) <-1.0f .. 1.0f>
    float throttle; // throttle position of the handle itself - this controls all the handles at once <0.0f .. 1.0f>
    float airSpeed; // aircraft airspeed in relation to its Vno <0.0f .. 1.0f+> (may exceed 1.0f)
    float propellerSpeed;   // propeller speed in [rpm]; the higher value of first 2 engines is used
};

class FlightControl
{
public:
    FlightControl(EventQueue& eventQueue);
    void handler(void);
    void connect(void);
private:
    void sendDataToSimulator(void);
    void setControls(void);
    EventQueue& eventQueue;             // event queue for flight control events
    USBHID* pConnection{nullptr};       // pointer to USB HID object
    static const uint8_t HIDBufferLength = 64;
    static const uint16_t USB_VID = 0x0483;
    static const uint16_t USB_PID = 0x5750;
    static const uint16_t USB_VER = 0x0002;
    HID_REPORT inputReport = {.length = HIDBufferLength, .data = {0}};      // report from simulator
    HID_REPORT outputReport = {.length = HIDBufferLength, .data = {0}};     // report to simulator
    Timeout simulatorDataTimeout;         // timeout object for receiving simulator data
    SimulatorData simulatorData;          // structure of received simulator data
    Timer controlTimer;                 // measures time between control loops
    float throttleLeverPosition{0.0f};  // throttle lever calculated position <0..1>
    AnalogIn propellerPotentiometer;    // propeller pitch potentiometer (blue)
    AnalogIn mixturePotentiometer;      // mixture potentiometer (red)
    float throttleLeverSpeed{0.0f};  // speed of the throttle lever
    const float ThrottleLeverFrictionCoefficient = 0.3f;
    const float ThrottleLeverSpeedCoefficient = 10.0f;
    const float ThrottleFilterAlpha = 0.25f;
};

#endif /* SOURCE_FLIGHTCONTROL_H_ */
