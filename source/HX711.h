/*
 * HX711.h
 *
 *  Created on: 23.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_HX711_H_
#define SOURCE_HX711_H_

#include "mbed.h"

class HX711
{
public:
    HX711(PinName dataPin, PinName clkPin, uint8_t noOfPulses = 25);
    void readData(void);
private:
    DigitalIn dataInput;        //XXX this should be changed to interrupt input
    DigitalOut clockOutput;     // clock signal
    uint8_t noOfPulses;         // this number must be in the range 25..27
    uint32_t dataBuffer;        // buffer for data readout
    uint32_t dataRegister;      // last received data register
};

#endif /* SOURCE_HX711_H_ */
