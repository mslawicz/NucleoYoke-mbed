/*
 * I2CDevice.cpp
 *
 *  Created on: 17.02.2020
 *      Author: Marcin
 */

#include "I2CDevice.h"

extern DigitalOut alarmLed;

I2CDevice::I2CDevice(I2C& bus, uint8_t deviceAddress) :
    bus(bus),
    address(deviceAddress)
{
}

/*
 * write to I2C device
 */
void I2CDevice::write(uint8_t registerAddress, std::vector<uint8_t> data)
{
    // insert register address byte at the front
    data.insert(data.begin(), registerAddress);
    if(bus.write(static_cast<int>(address), (const char*)&data[0], data.size()))
    {
        alarmLed = 1;
    }
}

/*
 * read from I2C device
 */
std::vector<uint8_t> I2CDevice::read(uint8_t registerAddress, uint8_t length)
{
    std::vector<uint8_t> data(length);
    if(bus.write(static_cast<int>(address), (const char*)&registerAddress, 1, true))
    {
        alarmLed = 1;
    }
    if(bus.read(static_cast<int>(address), (char*)&data[0], length))
    {
        alarmLed = 1;
    }
    return data;
}
