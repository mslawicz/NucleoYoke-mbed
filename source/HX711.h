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
    HX711(PinName dataPin, PinName clkPin, EventQueue& eventQueue, uint8_t noOfPulses = 25);
    void readData(void);
    uint32_t getDataRegister(void) const { return dataRegister; }
    float getValue(void) const { return value; }
private:
    void interruptHandler(void);
    InterruptIn dataInput;      // data input triggers interrupt and is used for reading data from device
    DigitalOut clockOutput;     // clock signal
    uint8_t noOfPulses;         // this number must be in the range 25..27
    uint32_t dataBuffer;        // buffer for data readout
    uint32_t dataRegister;      // last received data register
    EventQueue& eventQueue;     // event queue which is to handle data readout in main context
    float value;                // tensometer readout value in the range <-1.0f,1.0f>
    Reference reference;        // object for calculations of tensometer reference (zero) value
};

#endif /* SOURCE_HX711_H_ */
