/*
 * Servo.h
 *
 *  Created on: 24.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_SERVO_H_
#define SOURCE_SERVO_H_

#include "mbed.h"

class Servo
{
public:
    Servo(PinName pwmPin);
private:
    PwmOut pwmOut;
};

#endif /* SOURCE_SERVO_H_ */
