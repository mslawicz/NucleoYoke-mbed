/*
 * HX711.h
 *
 *  Created on: 23.12.2019
 *      Author: Marcin
 */

#ifndef SOURCE_HX711_H_
#define SOURCE_HX711_H_

#include "mbed.h"
#include "Reference.h"

class HX711
{
public:
    HX711(PinName dataPin, PinName clkPin, EventQueue& eventQueue, bool reverse = false, uint8_t noOfPulses = 25);
    void readData(void);
    uint32_t getDataRegister(void) const { return dataRegister; }
    float getUncalibratedValue(void) const { return reverse ? -uncalibratedValue : uncalibratedValue; }
    float getValue(void) const { return reverse ? -calibratedValue : calibratedValue; }
private:
    void interruptHandler(void);
    InterruptIn dataInput;      // data input triggers interrupt and is used for reading data from device
    DigitalOut clockOutput;     // clock signal
    uint8_t noOfPulses;         // this number must be in the range 25..27
    uint32_t dataBuffer;        // buffer for data readout
    uint32_t dataRegister;      // last received data register (24-bit integer right shifted)
    EventQueue& eventQueue;     // event queue which is to handle data readout in main context
    float uncalibratedValue;    // tensometer uncalibrated readout value in the range <-1.0f,1.0f>
    Reference reference;        // object for calculations of tensometer reference (zero) value
    float calibratedValue;      // tensometer calibrated value in the range <-1.0f,1.0f>
    bool reverse;               // if true, returned value has reversed sign
};

#endif /* SOURCE_HX711_H_ */
