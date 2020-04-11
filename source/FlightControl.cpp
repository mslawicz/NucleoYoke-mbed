/*
 * FlightControl.cpp
 *
 *  Created on: 19.12.2019
 *      Author: Marcin
 */

#include "main.h"
#include "FlightControl.h"
#include "platform/mbed_debug.h"

//XXX global data for STM Studio monitoring
VectorFloat g_gyro, g_acc, g_mag;
float g_pitch, g_roll, g_yaw;

FlightControl::FlightControl(EventQueue& eventQueue) :
    eventQueue(eventQueue),
    propellerPotentiometer(PC_1),
    mixturePotentiometer(PC_0),
    imuInterruptSignal(LSM6DS3_INT1),
    i2cBus(I2C1_SDA, I2C1_SCL),
    sensorGA(i2cBus, LSM6DS3_AG_ADD)
{
    i2cBus.frequency(400000);
}

/*
 * handler to be called from IMU sensor interrupt routine
 * it calculates control data and sends them to PC
 */
void FlightControl::handler(void)
{
    // this timeout is set only for the case of lacking IMU interrupts
    // the timeout should never happen, as the next interrupt should happen sooner
    imuIntTimeout.attach(callback(this, &FlightControl::imuInterruptHandler), 0.02f);

    // measure time elapsed since the previous call
    float deltaT = handlerTimer.read();
    handlerTimer.reset();

    // read IMU sensor data
    auto sensorData = sensorGA.read((uint8_t)LSM6DS3reg::OUT_X_L_G, 12);
    gyroscopeData.X = *reinterpret_cast<int16_t*>(&sensorData[0]);
    gyroscopeData.Y = *reinterpret_cast<int16_t*>(&sensorData[2]);
    gyroscopeData.Z = *reinterpret_cast<int16_t*>(&sensorData[4]);
    accelerometerData.X = *reinterpret_cast<int16_t*>(&sensorData[6]);
    accelerometerData.Y = *reinterpret_cast<int16_t*>(&sensorData[8]);
    accelerometerData.Z = *reinterpret_cast<int16_t*>(&sensorData[10]);

    // calculate IMU sensor physical values; using right hand rule
    // X = roll axis = pointing North
    // Y = pitch axis = pointing East
    // Z = yaw axis = pointing down
    // angular rate in rad/s
    angularRate.X = -AngularRateResolution * gyroscopeData.Z;
    angularRate.Y = AngularRateResolution * gyroscopeData.Y;
    angularRate.Z = -AngularRateResolution * gyroscopeData.X;
    // acceleration in g
    acceleration.X = -AccelerationResolution * accelerometerData.Z;
    acceleration.Y = -AccelerationResolution * accelerometerData.Y;
    acceleration.Z = -AccelerationResolution * accelerometerData.X;

    float accelerationXZ = sqrt(acceleration.X * acceleration.X + acceleration.Z * acceleration.Z);
    float accelerationYZ = sqrt(acceleration.Y * acceleration.Y + acceleration.Z * acceleration.Z);

    // calculate pitch and roll from accelerometer itself
    float accelerometerPitch = atan2(acceleration.X, accelerationYZ);
    float accelerometerRoll = atan2(acceleration.Y, accelerationXZ);

    // calculate sensor pitch and roll using complementary filter
    sensorPitch = (1.0f - ComplementaryFilterFactor) * (sensorPitch + angularRate.Y * deltaT) + ComplementaryFilterFactor * accelerometerPitch;
    sensorRoll = (1.0f - ComplementaryFilterFactor) * (sensorRoll + angularRate.X * deltaT) + ComplementaryFilterFactor * accelerometerRoll;

    // calculate sensor relative yaw with autocalibration
    sensorYaw = 0.999f * (sensorYaw + angularRate.Z * deltaT);

    float sin2yaw = sin(sensorYaw) * fabs(sin(sensorYaw));
    float cos2yaw = cos(sensorYaw) * fabs(cos(sensorYaw));

    // calculate joystick pitch and roll depending on the joystick yaw
    float joystickPitch = sensorPitch * cos2yaw + sensorRoll * sin2yaw;
    float joystickRoll = sensorRoll * cos2yaw - sensorPitch * sin2yaw;

    joystickData.X = scale<float, int16_t>(-1.5f, 1.5f, joystickRoll, -32767, 32767);
    joystickData.Y = scale<float, int16_t>(-1.0f, 1.0f, joystickPitch, -32767, 32767);
    joystickData.Z = scale<float, int16_t>(-1.0f, 1.0f, sensorYaw, -32767, 32767);

    // send HID joystick report to PC
    pJoystick->sendReport(joystickData);

    //XXX global data for STM Studio
    g_gyro = angularRate;
    g_acc = acceleration;
    g_pitch = joystickPitch;
    g_roll = joystickRoll;
    g_yaw = sensorYaw;
}

/*
 * connect to simulator using USB HID connection
 */
void FlightControl::connect(void)
{
    // create and start USB HID device object in a disconnected state
    //pConnection = new USBHID(false, HIDBufferLength, HIDBufferLength, USB_VID, USB_PID, USB_VER);
    // create and start USB HID Joystick device object in a disconnected state
    pJoystick = new USBJoystick(USB_VID, USB_PID, USB_VER);
    // start joystick connection process
    pJoystick->connect();
    debug("Connecting to PC using USB HID joystick (VID=%#06X PID=%#06X ver=%d)\r\n", USB_VID, USB_PID, USB_VER);
}

/*
 * prepares data in the output report and sends the report to simulator
 */
//void FlightControl::sendDataToSimulator(void)
//{
//    outputReport.data[0] = 0;
//
//    // bytes 4-7 is the bitfield data register (buttons, switches, encoders)
//    uint32_t buttons = 0;
//    buttons |= (0 << 0);    // bit 0 - flaps up (one shot switch)
//    buttons |= (0 << 1);  // bit 1 - flaps down (one shot switch)
//    buttons |= (0 << 2);  // bit 2 - gear up (one shot switch)
//    buttons |= (0 << 3);  // bit 3 - gear down (one shot switch)
//    buttons |= (0 << 4);  // bit 4 - center pilot's view (analog joystick pushbutton) (one shot switch)
//    buttons |= (1 << 5);  // bit 5 - elevator trim up button, 0=active
//    buttons |= (1 << 6);  // bit 6 - elevator trim down button, 0=active
//    memcpy(outputReport.data+4, &buttons, sizeof(buttons));
//
//    float fParameter;
//    // bytes 8-11 for yoke pitch
//    fParameter = 0.0f;
//    memcpy(outputReport.data+8, &fParameter, sizeof(fParameter));
//    // bytes 12-15 for yoke roll
//    fParameter = 0.0f;
//    memcpy(outputReport.data+12, &fParameter, sizeof(fParameter));
//    // bytes 16-19 for rudder control
//    fParameter = 0.2f;
//    memcpy(outputReport.data+16, &fParameter, sizeof(fParameter));
//    // bytes 24-27 for mixture control
//    fParameter = 1.0f;
//    memcpy(outputReport.data+24, &fParameter, sizeof(fParameter));
//    // bytes 28-31 for propeller control
//    fParameter = 1.0f;
//    memcpy(outputReport.data+28, &fParameter, sizeof(fParameter));
//    // bytes 32-35 for analog joystick Y (pilot's view yaw)
//    fParameter = 0.0f;
//    memcpy(outputReport.data+32, &fParameter, sizeof(fParameter));
//    // bytes 36-39 for analog joystick X (pilot's view pitch)
//    fParameter = 0.0f;
//    memcpy(outputReport.data+36, &fParameter, sizeof(fParameter));
//
//    pConnection->send_nb(&outputReport);
//}

/*
 * configures Flight Control object
 */
void FlightControl::config(void)
{
    // INT1<-DRDY_G
    sensorGA.write((uint8_t)LSM6DS3reg::INT1_CTRL, std::vector<uint8_t>{0x02});
    // Gyroscope ODR=119 Hz, full scale 500 dps, cutoff 31 Hz
    // int/out selection default
    // low power disable, HPF enable, HPF=0.05 Hz
    sensorGA.write((uint8_t)LSM6DS3reg::CTRL_REG1_G, std::vector<uint8_t>{0x69, 0x00, 0x47});
    // Accelerometer ODR=119 Hz, full scale +=2g, default bandwith
    sensorGA.write((uint8_t)LSM6DS3reg::CTRL_REG6_XL, std::vector<uint8_t>{0x60});

    imuInterruptSignal.rise(callback(this, &FlightControl::imuInterruptHandler));
    // this timeout calls imuInterruptHandler for the first time
    // next calls will be executed upon IMU INT1 interrupt signal
    imuIntTimeout.attach(callback(this, &FlightControl::imuInterruptHandler), 0.1f);

    // start handler timer
    handlerTimer.start();
}

/*
 * IMU sensor interrupt handler
 */
void FlightControl::imuInterruptHandler(void)
{
    eventQueue.call(callback(this, &FlightControl::handler));
}
