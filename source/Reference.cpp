/*
 * Reference.cpp
 *
 *  Created on: 26.12.2019
 *      Author: Marcin
 */

#include "Reference.h"

Reference::Reference(float midValue, float calculationLimit, float referenceDeviationLimit, uint32_t stableSamples) :
    midValue(midValue),
    calculationLimit(calculationLimit),
    referenceDeviationLimit(referenceDeviationLimit),
    stableSamples(stableSamples)
{
    referenceValue = midValue;
}

// calculates reference according to input values
void Reference::calculateReference(float inputValue)
{
    if ((inputValue > midValue - calculationLimit) &&
        (inputValue < midValue + calculationLimit))
    {
        // input value in the allowed range of reference value
        if (++noOfAveragedSamples == 1)
        {
            // the first valid sample
            averageValue = inputValue;
        }

        if (fabs(inputValue - averageValue) < referenceDeviationLimit)
        {
            // input value in allowed deviation range
            averageValue = (averageValue * (noOfAveragedSamples - 1) + inputValue) / noOfAveragedSamples;
        }
        else
        {
            // input value out of allowed deviation range
            noOfAveragedSamples = 0;
        }

        if (noOfAveragedSamples > stableSamples)   // enough stable samples within limit
        {
            referenceValue = averageValue;
        }
    }
    else
    {
        // input value out of allowed range
        noOfAveragedSamples = 0;
    }
}
