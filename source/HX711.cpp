/*
 * HX711.cpp
 *
 *  Created on: 23.12.2019
 *      Author: Marcin
 */

#include "HX711.h"
#include "platform/mbed_critical.h"

void testFunction(void) {}

HX711::HX711(PinName dataPin, PinName clkPin, EventQueue* pEventQueue, uint8_t noOfPulses) :
    dataInput(dataPin),
    clockOutput(clkPin),
    noOfPulses(noOfPulses),
    pEventQueue(pEventQueue)
{
    MBED_ASSERT((noOfPulses >= 25) && (noOfPulses <= 27));
    clockOutput = 0;
    dataBuffer = 0;
    dataRegister = 0;
    dataInput.fall(callback(this, &HX711::interruptHandler));
}

/*
 * read data from HX711 device
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
    dataInput.enable_irq();
}

/*
 * this interrupt routine is called on falling edge of HX711 data signal
 * this routine only commissions the data readout in the event dispatch thread
 */
void HX711::interruptHandler(void)
{
    if(pEventQueue != nullptr)
    {
        pEventQueue->call(callback(this, &HX711::readData));
    }
}
