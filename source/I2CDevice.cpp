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

