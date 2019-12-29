/*
 * SH1106.cpp
 *
 *  Created on: 25.12.2019
 *      Author: Marcin
 */

#include "SH1106.h"

SH1106::SH1106(PinName dataPin, PinName clkPin, PinName resetPin, PinName cdPin, PinName csPin) :
    interface(dataPin, NC, clkPin),
    resetSignal(PE_15),
    cdSignal(cdPin),
    csSignal(csPin)
{
    csSignal = 1;
}

/*
 * initialization of SH1106 controller
 */
void SH1106::init(void)
{
    resetSignal = 0;
    resetSignal = 1;
    // wait after reset
    ThisThread::sleep_for(1);
    // send initialization data
    write(SH1106InitData, true);
    // clear screen
    update();
    //display on
    write(std::vector<uint8_t>{0xAF}, true);
    // wait after init
    ThisThread::sleep_for(100);
}

/*
 * updates display according to the range in updateArray
 */
void SH1106::update(void)
{
    // check update of every page
    for(uint8_t page = 0; page < noOfPages; page++)
    {
        // check wether this page must be updated
        if((updateArray[page][0] < sizeX) && (updateArray[page][1] < sizeX))
        {
            // send data from buffer to display
            write(&dataBuffer[page][updateArray[page][0]], updateArray[page][1]-updateArray[page][0]+1);
            // clear the range to update
            updateArray[page][0] = updateArray[page][1] = 0xFF;
        }
    }
}

/*
 * send command/data to display controller
 */
void SH1106::write(uint8_t* data, int length, bool command)
{
    cdSignal = command ? 0 : 1;
    csSignal = 0;
    interface.write((const char*)data, length, nullptr, 0);
    csSignal = 1;
}

