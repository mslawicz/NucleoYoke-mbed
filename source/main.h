/*
 * main.h
 *
 *  Created on: 21.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_MAIN_H_
#define SOURCE_MAIN_H_

#include "mbed.h"

struct VectorInt16
{
    int16_t X;
    int16_t Y;
    int16_t Z;
};

struct VectorFloat
{
    float X;
    float Y;
    float Z;
};

template<typename iType, typename oType> oType scale(iType iMin, iType iMax, iType input, oType oMin, oType oMax, bool limit = true)
{
    auto result = static_cast<oType>(1.0f * (input-iMin) / (iMax-iMin) * (oMax-oMin) + oMin);
    if(limit)
    {
        if(result < oMin)
        {
            result = oMin;
        }
        else if(result > oMax)
        {
            result = oMax;
        }
    }
    return result;
}

#endif /* SOURCE_MAIN_H_ */
