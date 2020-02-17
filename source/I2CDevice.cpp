/*
 * I2CDevice.cpp
 *
 *  Created on: 17.02.2020
 *      Author: Marcin
 */

#include "I2CDevice.h"

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
}

/*
 * read from I2C device
 */
std::vector<uint8_t> I2CDevice::read(uint8_t registerAddress, uint8_t length)
{
    std::vector<uint8_t> data(length);

    return data;
}
