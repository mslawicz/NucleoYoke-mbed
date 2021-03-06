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
    sensorGA(i2cBus, LSM6DS3_AG_ADD),
    calibrationLed(LED2)
{
    i2cBus.frequency(400000);
    calibrationLed = 0;
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

    // store sensor values for calculation of deviation
    float previousSensorPitch = sensorPitch;
    float previousSensorRoll = sensorRoll;

    // calculate sensor pitch and roll using complementary filter
    const float SensorFilterFactor = 0.02f;
    sensorPitch = (1.0f - SensorFilterFactor) * (sensorPitch + angularRate.Y * deltaT) + SensorFilterFactor * accelerometerPitch;
    sensorRoll = (1.0f - SensorFilterFactor) * (sensorRoll + angularRate.X * deltaT) + SensorFilterFactor * accelerometerRoll;

    // calculate sensor pitch and roll variability
    const float variabilityFilterFactor = 0.01f;
    float reciprocalDeltaT = (deltaT > 0.0f) ? (1.0f / deltaT) : 1.0f;
    sensorPitchVariability = (1.0f - variabilityFilterFactor) * sensorPitchVariability + variabilityFilterFactor * fabs(sensorPitch - previousSensorPitch) * reciprocalDeltaT;
    sensorRollVariability = (1.0f - variabilityFilterFactor) * sensorRollVariability + variabilityFilterFactor * fabs(sensorRoll - previousSensorRoll) * reciprocalDeltaT;

    // store sensor pitch and roll reference value
    const float sensorVariabilityThreshold = 0.0025f;
    if((sensorPitchVariability < sensorVariabilityThreshold) &&
       (sensorRollVariability < sensorVariabilityThreshold))
    {
        sensorPitchReference = sensorPitch;
        sensorRollReference = sensorRoll;
        calibrationLed = 1;
    }
    else
    {
        calibrationLed = 0;
    }

    // calculate sensor calibrated values
    float calibratedSensorPitch = sensorPitch - sensorPitchReference;
    float calibratedSensorRoll = sensorRoll - sensorRollReference;

    // calculate sensor relative yaw
    sensorYaw += angularRate.Z * deltaT;

    // autocalibration of yaw
    const float YawAutocalibrationThreshold = 0.15f;    // joystick deflection threshold for disabling yaw autocalibration function
    const float YawAutocalibrationFactor = 0.9999f;      // yaw autocalibration factor
    float joystickDeflection = sqrt(calibratedSensorPitch * calibratedSensorPitch + calibratedSensorRoll * calibratedSensorRoll);
    if(joystickDeflection < YawAutocalibrationThreshold)
    {
        sensorYaw *= YawAutocalibrationFactor;
    }

    // calculate joystick pitch and roll depending on the joystick yaw
    float sin2yaw = sin(sensorYaw) * fabs(sin(sensorYaw));
    float cos2yaw = cos(sensorYaw) * fabs(cos(sensorYaw));

    float joystickPitch = calibratedSensorPitch * cos2yaw + calibratedSensorRoll * sin2yaw;
    float joystickRoll = calibratedSensorRoll * cos2yaw - calibratedSensorPitch * sin2yaw;

    // scale joystick axes to USB joystick report range
    joystickData.X = scale<float, int16_t>(-1.5f, 1.5f, joystickRoll, -32767, 32767);
    joystickData.Y = scale<float, int16_t>(-1.0f, 1.0f, joystickPitch, -32767, 32767);
    joystickData.Z = scale<float, int16_t>(-0.75f, 0.75f, sensorYaw, -32767, 32767);

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
 * display status of FlightControl
 */
void FlightControl::displayStatus(CommandVector cv)
{
    printf("IMU sensor pitch = %f\r\n", sensorPitch);
    printf("IMU sensor roll = %f\r\n", sensorRoll);
    printf("IMU sensor yaw = %f\r\n", sensorYaw);
    printf("joystick X = %d\r\n", joystickData.X);
    printf("joystick Y = %d\r\n", joystickData.Y);
    printf("joystick Z = %d\r\n", joystickData.Z);
    printf("joystick Rx = %d\r\n", joystickData.Rx);
    printf("joystick Ry = %d\r\n", joystickData.Ry);
    printf("joystick Rz = %d\r\n", joystickData.Rz);
    printf("joystick hat = 0x%02X\r\n", joystickData.hat);
    printf("joystick buttons = 0x%04X\r\n", joystickData.buttons);
}

/*
 * IMU sensor interrupt handler
 */
void FlightControl::imuInterruptHandler(void)
{
    eventQueue.call(callback(this, &FlightControl::handler));
}
