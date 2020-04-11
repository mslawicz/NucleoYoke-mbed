/*
 * FlightControl.h
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_FLIGHTCONTROL_H_
#define SOURCE_FLIGHTCONTROL_H_

#include "main.h"
#include "Console.h"
#include "Display.h"
#include "USBJoystick.h"
#include "I2CDevice.h"
#include "mbed.h"
#include "drivers/USBHID.h"

#define I2C1_SCL    PB_8
#define I2C1_SDA    PB_9

#define LSM6DS3_AG_ADD  0xD6
#define LSM6DS3_INT1    PB_6

enum struct LSM6DS3reg : uint8_t
{
    INT1_CTRL = 0x0C,
    CTRL_REG1_G = 0x10,
    OUT_X_L_G = 0x18,
    CTRL_REG6_XL = 0x20
};

class FlightControl
{
public:
    FlightControl(EventQueue& eventQueue);
    void handler(void);
    void connect(void);
    void config(void);
private:
    void imuInterruptHandler(void);
    EventQueue& eventQueue;             // event queue for flight control events
    //USBHID* pConnection{nullptr};       // pointer to USB HID object
    USBJoystick* pJoystick{nullptr};    // pointer to USB HID Joystick device
    static const uint8_t HIDBufferLength = 64;
    static const uint16_t USB_VID = 0x0483; //STElectronics
    static const uint16_t USB_PID = 0x5711; //joystick in FS mode + 1
    static const uint16_t USB_VER = 0x0003; //Nucleo Yoke ver. 3
    HID_REPORT inputReport = {.length = HIDBufferLength, .data = {0}};      // report from simulator
    HID_REPORT outputReport = {.length = HIDBufferLength, .data = {0}};     // report to simulator
    AnalogIn propellerPotentiometer;    // propeller pitch potentiometer (blue)
    AnalogIn mixturePotentiometer;      // mixture potentiometer (red)
    InterruptIn imuInterruptSignal;     //IMU sensor interrupt signal
    JoystickData joystickData;
    I2C i2cBus;                         // I2C bus for IMU sensor
    I2CDevice sensorGA;                 // IMU gyroscope and accelerometer sensor
    Timeout imuIntTimeout;              // timeout of the IMU sensor interrupts
    VectorInt16 gyroscopeData;          // raw data from gyroscope sensor
    VectorInt16 accelerometerData;      // raw data from accelerometer sensor
    VectorFloat angularRate;            // measured IMU sensor angular rate in rad/s
    VectorFloat acceleration;           // measured IMU sensor acceleration in g
    const float AngularRateResolution = 500.0f * 3.14159265f / 180.0f / 32768.0f;   // 1-bit resolution of angular rate in rad/s
    const float AccelerationResolution = 2.0f / 32768.0f;   // 1-bit resolution of acceleration in g
    Timer handlerTimer;
    float sensorPitch{0.0f}, sensorRoll{0.0f}, sensorYaw{0.0f};             // orientation of the IMU sensor
    const float ComplementaryFilterFactor = 0.02f;
};

#endif /* SOURCE_FLIGHTCONTROL_H_ */
