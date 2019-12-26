/*
 * Servo.cpp
 *
 *  Created on: 24.12.2019
 *      Author: Marcin
 */

#include "main.h"
#include "Servo.h"

Servo::Servo(PinName pwmPin, float minPulseWidth, float maxPulseWidth, float startValue, bool reverse) :
    pwmOut(pwmPin),
    minPulseWidth(minPulseWidth),
    maxPulseWidth(maxPulseWidth),
    startValue(startValue),
    reverse(reverse)
{
    setValue(startValue);
}

/*
 * set servo value in the range <0..1>
 */
void Servo::setValue(float value)
{
    pwmOut.pulsewidth(convert<float, float>(0.0f, 1.0f, reverse ? (1.0f-value) : value, minPulseWidth, maxPulseWidth));
}
