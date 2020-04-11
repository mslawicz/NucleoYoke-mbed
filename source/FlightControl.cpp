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
    angularRate.X = -AngularRateResolution * gyroscopeData.X;
    angularRate.Y = AngularRateResolution * gyroscopeData.Y;
    angularRate.Z = -AngularRateResolution * gyroscopeData.Z;
    // acceleration in g
    acceleration.X = -AccelerationResolution * accelerometerData.X;
    acceleration.Y = -AccelerationResolution * accelerometerData.Y;
    acceleration.Z = -AccelerationResolution * accelerometerData.Z;

    float accelerationXZ = sqrt(acceleration.X * acceleration.X + acceleration.Z * acceleration.Z);
    float accelerationYZ = sqrt(acceleration.Y * acceleration.Y + acceleration.Z * acceleration.Z);

    // calculate pitch and roll from accelerometer itself
    float accelerometerPitch = atan2(acceleration.X, accelerationYZ);
    float accelerometerRoll = atan2(acceleration.Y, accelerationXZ);

    // calculate sensor pitch and roll using complementary filter
    sensorPitch = (1.0f - ComplementaryFilterFactor) * (sensorPitch + angularRate.Y * deltaT) + ComplementaryFilterFactor * accelerometerPitch;
    sensorRoll = (1.0f - ComplementaryFilterFactor) * (sensorRoll + angularRate.X * deltaT) + ComplementaryFilterFactor * accelerometerRoll;

    static float tilt = 0.0f;
    tilt = tilt * 0.99f + 0.01f * (fabs(sensorPitch) + fabs(sensorRoll));

    // calculate sensor relative yaw with autocalibration
    sensorYaw += angularRate.Z * deltaT;

    if(tilt < 0.1f)
    {
        sensorYaw *= 0.99f;
    }

    float sin2yaw = sin(sensorYaw) * fabs(sin(sensorYaw));
    float cos2yaw = cos(sensorYaw) * fabs(cos(sensorYaw));

    // calculate joystick pitch and roll depending on the joystick yaw
    float joystickPitch = sensorPitch * cos2yaw + sensorRoll * sin2yaw;
    float joystickRoll = sensorRoll * cos2yaw - sensorPitch * sin2yaw;

    joystickData.X = scale<float, int16_t>(-1.5f, 1.5f, joystickRoll, -32767, 32767);
    joystickData.Y = scale<float, int16_t>(-1.0f, 1.0f, joystickPitch, -32767, 32767);
    joystickData.Z = scale<float, int16_t>(-0.75f, 0.75f, sensorYaw, -32767, 32767);

    // send HID joystick report to PC
    pJoystick->sendReport(joystickData);

    //XXX global data for STM Studio
    g_gyro = angularRate;
    g_acc = acceleration;
    g_pitch = tilt;//joystickPitch;
    g_roll = sensorRoll;//joystickRoll;
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
 * configures Flight Control object
 */
void FlightControl::config(void)
{
    // INT1<-DRDY_G
    sensorGA.write((uint8_t)LSM6DS3reg::INT1_CTRL, std::vector<uint8_t>{0x02});
    // accelerometer ODR=104 Hz, full scale 2g, antialiasing 400 Hz
    // gyroscope ODR=104 Hz, full scale 500 dps,
    sensorGA.write((uint8_t)LSM6DS3reg::CTRL1_XL, std::vector<uint8_t>{0x40, 0x44});
    // gyroscope HPF enable, HPF=0.0081 Hz
    sensorGA.write((uint8_t)LSM6DS3reg::CTRL7_G, std::vector<uint8_t>{0x40});


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
