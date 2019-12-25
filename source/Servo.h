/*
 * Servo.h
 *
 *  Created on: 24.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_SERVO_H_
#define SOURCE_SERVO_H_

#include "mbed.h"

//min, -90, 0, 90, max [ms]
//DS3218 (180): 0.45, 0.55, 1.5, 2.51, 2.55
//RDS3225 (270): 0.47, 0.87, 1.5, 2.17, 2.46
//RDS3235 (180): 0.48, 0.57, 1.5, 2.45, 2.56

class Servo
{
public:
    Servo(PinName pwmPin);
    void test(float pulseWidth) { pwmOut.pulsewidth(pulseWidth); }
private:
    PwmOut pwmOut;
};

#endif /* SOURCE_SERVO_H_ */
