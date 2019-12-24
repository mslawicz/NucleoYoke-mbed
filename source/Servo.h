/*
 * Servo.h
 *
 *  Created on: 24.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_SERVO_H_
#define SOURCE_SERVO_H_

#include "mbed.h"

//min, -90, 0, 90, max
//DS3218: 0.45, 0.55, 1.5, 2.51, 2.55

class Servo
{
public:
    Servo(PinName pwmPin);
    void test(float pulseWidth) { pwmOut.pulsewidth(pulseWidth); }
private:
    PwmOut pwmOut;
};

#endif /* SOURCE_SERVO_H_ */
