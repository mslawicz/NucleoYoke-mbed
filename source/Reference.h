/*
 * Reference.h
 *
 *  Created on: 26.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_REFERENCE_H_
#define SOURCE_REFERENCE_H_

#include "mbed.h"

class Reference
{
public:
    Reference(float midValue, float calculationLimit, float referenceDeviationLimit, uint32_t stableSamples);
    void calculateReference(float inputValue);
    float getReference(void) const { return referenceValue; }
private:
    float midValue;                 // middle (expected) value of the input range
    float calculationLimit;         // only values within this limit are taken into calculations
    float referenceDeviationLimit;  // allowed deviation from current reference value of measurements taken into calculations
    uint32_t stableSamples;         // number of samples which must be within allowed range before the new reference is accepted
    uint32_t noOfAveragedSamples {0};   // number of averaged samples
    float averageValue {0.0f};      // samples average value being calculated
    float referenceValue;           // current measured and accepted reference value
};

#endif /* SOURCE_REFERENCE_H_ */
