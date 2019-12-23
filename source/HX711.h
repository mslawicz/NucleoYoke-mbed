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
    HX711(PinName dataPin, PinName clkPin, EventQueue* pEventQueue, uint8_t noOfPulses = 25);
    void readData(void);
private:
    void interruptHandler(void);
    InterruptIn dataInput;      // data input triggers interrupt and is used for reading data from device
    DigitalOut clockOutput;     // clock signal
    uint8_t noOfPulses;         // this number must be in the range 25..27
    uint32_t dataBuffer;        // buffer for data readout
    uint32_t dataRegister;      // last received data register
    EventQueue* pEventQueue;    // pointer to event queue which is to handle data readout in main context
};

#endif /* SOURCE_HX711_H_ */
