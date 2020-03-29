/*
 * USBJoystick.h
 *
 *  Created on: 05.02.2020
 *      Author: Marcin
 */

#ifndef SOURCE_USBYOKE_H_
#define SOURCE_USBYOKE_H_

#include "USBHID.h"
#include <vector>

#define REPORT_ID_JOYSTICK 1
#define REPORT_ID_FF 2

struct JoystickData
{
    int16_t X;
    int16_t Y;
    int16_t Z;
    int16_t Rx;
    int16_t Ry;
    int16_t Rz;
    uint8_t hat;
    uint16_t buttons;
};

class USBYoke : public USBHID
{
public:
    USBYoke(uint16_t vendorId, uint16_t productId, uint16_t productRelease, bool blocking = false);
    virtual ~USBYoke();
    virtual const uint8_t* report_desc(); // returns pointer to the report descriptor; Warning: this method has to store the length of the report descriptor in reportLength
    bool sendReport(uint8_t reportID, std::vector<uint8_t> data);
protected:
    virtual const uint8_t* configuration_desc(uint8_t index);   // Get configuration descriptor; returns pointer to the configuration descriptor
private:
    uint8_t configurationDescriptor[41];
};

#endif /* SOURCE_USBYOKE_H_ */
