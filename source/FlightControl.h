/*
 * FlightControl.h
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_FLIGHTCONTROL_H_
#define SOURCE_FLIGHTCONTROL_H_

#include "Servo.h"
#include "WS2812.h"
#include "HX711.h"
#include "USBYoke.h"
#include "Console.h"
#include "Display.h"
#include "mbed.h"

enum class ControlMode : uint8_t
{
    force_feedback,
    spring,
    demo,
    end
};

struct JoystickData
{
    int16_t X;
    int16_t Y;
    int16_t Z;
    int16_t Rx;
    int16_t Ry;
    int16_t Rz;
    int16_t slider;
    int16_t dial;
    int16_t wheel;
    uint8_t hat;
    uint16_t buttons;
};

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
    void displaySimulatorData(CommandVector cv);
    void displayTensometerValues(CommandVector cv);
    void changeControlMode(int change = 0);
private:
    void markSimulatorDataInactive(void);
    void parseReceivedData(void);
    void sendJoystickData(void);
    void setControls(void);
    void updateIndicators(void);
    EventQueue& eventQueue;             // event queue for flight control events
    USBYoke* pUSB{nullptr};	            // pointer to USB HID object
    WS2812 RGBLeds;                     // RGB LEDs object to indicate gear and flaps state
    static const uint8_t HIDBufferLength = 64;
    static const uint16_t USB_VID = 0x0483;
    static const uint16_t USB_PID = 0x5711;		//joystick in FS mode + 1
    //static const uint16_t USB_PID = 0x5750;
    static const uint16_t USB_VER = 0x0004;
    HID_REPORT inputReport = {.length = 0, .data = {0}};      // report from simulator
    HID_REPORT outputReport = {.length = 0, .data = {0}};     // report to simulator
    Timeout simulatorDataTimeout;         // timeout object for receiving simulator data
    DigitalOut simulatorDataIndicator;    // indicator of received simulator data
    SimulatorData simulatorData;          // structure of received simulator data
    bool newDataReceived{false};          // true if new data has been received in handler
    bool simulatorDataActive{false};      // true if simulator data is periodically being rceived and is active
    Servo pitchServo;
    Servo rollServo;
    Servo throttleServo;
    HX711 throttleTensometer;           // HX711 tensometer ADC for throttle input
    ControlMode controlMode{ControlMode::force_feedback};
    Timer controlTimer;                 // measures time between control loops
    float throttleLeverPosition{0.0f};  // throttle lever calculated position <0..1>
    AnalogIn propellerPotentiometer;    // propeller pitch potentiometer (blue)
    AnalogIn mixturePotentiometer;      // mixture potentiometer (red)
    AnalogIn autorudderPotentiometer;   // autorudder potentiometer (white)
    AnalogIn leftBrakePotentiometer;    // left brake potentiometer (left slider on main panel)
    AnalogIn rightBrakePotentiometer;   // right brake potentiometer (right slider on main panel)
    float throttleLeverSpeed{0.0f};  // speed of the throttle lever
    const float ThrottleLeverFrictionCoefficient = 0.3f;
    const float ThrottleLeverSpeedCoefficient = 10.0f;
    const float ThrottleFilterAlpha = 0.25f;
    HX711 pitchTensometer;              // HX711 tensometer ADC for pitch input
    JoystickData joystickData;          // joystick data to be sent to PC
    const int16_t minAxisValue = -32767;    // minimum value of joystick axis
    const int16_t maxAxisValue = 32767;    // maximum value of joystick axis
};

#endif /* SOURCE_FLIGHTCONTROL_H_ */
