/*
 * HX711.cpp
 *
 *  Created on: 23.12.2019
 *      Author: Marcin
 */

#include "HX711.h"
#include "main.h"
#include "platform/mbed_critical.h"

float g_tensUncalibr;   //XXX global variable for testing
float g_tensCalibr;   //XXX global variable for testing
float g_tensRef;        // XXX reference value of the tensometer

void testFunction(void) {}

HX711::HX711(PinName dataPin, PinName clkPin, EventQueue& eventQueue, bool reverse, uint8_t noOfPulses) :
    dataInput(dataPin),
    clockOutput(clkPin),
    noOfPulses(noOfPulses),
    eventQueue(eventQueue),
    reverse(reverse),
    reference(0.0f, 0.01, 0.001, 100)
{
    MBED_ASSERT((noOfPulses >= 25) && (noOfPulses <= 27));
    clockOutput = 0;
    dataBuffer = 0;
    dataRegister = 0;
    dataInput.fall(callback(this, &HX711::interruptHandler));
}

/*
 * read data from HX711 device
 * this method must be called in low priority event dispatch thread
 */
void HX711::readData(void)
{
    dataInput.disable_irq();
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
    // convert 24-bit int data register to float value in the range <-1..1>
    uncalibratedValue = convert<int, float>(-0x800000, 0x7Fffff, static_cast<int>(dataRegister << 8) / 256, -1.0f, +1.0f);
    reference.calculateReference(uncalibratedValue);
    calibratedValue = uncalibratedValue - reference.getReference();
    g_tensUncalibr = uncalibratedValue; //XXX
    g_tensCalibr = calibratedValue; //XXX
    g_tensRef = reference.getReference(); //XXX
    dataInput.enable_irq();
}

/*
 * this interrupt routine is called on falling edge of HX711 data signal
 * this routine only commissions the data readout in the event dispatch thread
 */
void HX711::interruptHandler(void)
{
    eventQueue.call(callback(this, &HX711::readData));
}
