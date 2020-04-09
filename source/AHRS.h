/*
 * AHRS.h
 *
 *  Created on: 09.04.2020
 *      Author: marci
 */

#ifndef SOURCE_AHRS_H_
#define SOURCE_AHRS_H_

#include "mbed.h"

class MadgwickFilter
{
public:
    MadgwickFilter(float beta);
    void update9DOF(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float dt);
    void update6DOF(float gx, float gy, float gz, float ax, float ay, float az, float dt);
    float getPitch(void) {return atan2f(2.0f * q2 * q3 - 2.0f * q0 * q1, 2.0f * q0 * q0 + 2.0f * q3 * q3 - 1.0f);};
    float getRoll(void) {return -1.0f * asinf(2.0f * q1 * q3 + 2.0f * q0 * q2);};
    float getYaw(void) {return atan2f(2.0f * q1 * q2 - 2.0f * q0 * q3, 2.0f * q0 * q0 + 2.0f * q1 * q1 - 1.0f);};
private:
    static float invSqrt(float x);
    void computeAngles();
    float q0{1.0f};
    float q1{0.0f};
    float q2{0.0f};
    float q3{0.0f};
    float beta;  // algorithm gain
};

#endif /* SOURCE_AHRS_H_ */
