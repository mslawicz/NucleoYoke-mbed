/*
 * HX711.cpp
 *
 *  Created on: 23.12.2019
 *      Author: Marcin
 */

#include "HX711.h"
#include "platform/mbed_critical.h"

HX711::HX711(PinName dataPin, PinName clkPin, uint8_t noOfPulses) :
    dataInput(dataPin),
    clockOutput(clkPin),
    noOfPulses(noOfPulses)
{
    MBED_ASSERT((noOfPulses >= 25) && (noOfPulses <= 27));
    clockOutput = 0;
    dataBuffer = 0;
    dataRegister = 0;
}

/*
 * read data from HX711 device
 */
void HX711::receiveData(void)
{
    dataBuffer = 0;
    for(uint8_t pulseNo = 0; pulseNo < noOfPulses; pulseNo++)
    {
        CriticalSectionLock lock;
        clockOutput = 1;
        if(pulseNo < 24)
        {
            dataBuffer <<= 1;
            dataBuffer |= (dataInput & 0x01);
        }
        clockOutput = 0;
    }
    dataRegister = dataBuffer;
}
