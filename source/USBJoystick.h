/*
 * USBJoystick.h
 *
 *  Created on: 05.02.2020
 *      Author: Marcin
 */

#ifndef SOURCE_USBJOYSTICK_H_
#define SOURCE_USBJOYSTICK_H_

#include "USBHID.h"

class USBJoystick : public USBHID
{
public:
    USBJoystick(uint16_t vendorId, uint16_t productId, uint16_t productRelease, bool blocking = false);
    virtual ~USBJoystick();
    virtual const uint8_t* report_desc(); // returns pointer to the report descriptor; Warning: this method has to store the length of the report descriptor in reportLength
protected:
    virtual const uint8_t* configuration_desc(uint8_t index);   // Get configuration descriptor; returns pointer to the configuration descriptor
private:
    uint8_t _configuration_descriptor[41];
};

#endif /* SOURCE_USBJOYSTICK_H_ */
