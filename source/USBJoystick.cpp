/*
 * USBJoystick.cpp
 *
 *  Created on: 05.02.2020
 *      Author: Marcin
 */

#include "USBJoystick.h"
#include "usb_phy_api.h"

USBJoystick::USBJoystick(uint16_t vendorId, uint16_t productId, uint16_t productRelease, bool blocking) :
    USBHID(get_usb_phy(), 0, 0, vendorId, productId, productRelease)
{
    if (blocking)
    {
        USBDevice::connect();
        wait_ready();
    }
    else
    {
        init();
    }
}

USBJoystick::~USBJoystick()
{
    deinit();
}

const uint8_t* USBJoystick::report_desc()
{
    static const uint8_t report_descriptor[] =
    {
        USAGE_PAGE(1),
        0x01,       // Genric Desktop
        USAGE(1),
        0x02,       // Mouse
        COLLECTION(1),
        0x01,       // Application
        USAGE(1),
        0x01,       // Pointer
        COLLECTION(1),
        0x00,       // Physical

        REPORT_COUNT(1), 0x03, REPORT_SIZE(1), 0x01, USAGE_PAGE(1),
        0x09,       // Buttons
        USAGE_MINIMUM(1), 0x1, USAGE_MAXIMUM(1), 0x3, LOGICAL_MINIMUM(1),
        0x00, LOGICAL_MAXIMUM(1), 0x01, INPUT(1), 0x02, REPORT_COUNT(1),
        0x01, REPORT_SIZE(1), 0x05, INPUT(1), 0x01,

        REPORT_COUNT(1), 0x03, REPORT_SIZE(1), 0x08, USAGE_PAGE(1), 0x01,
        USAGE(1), 0x30,       // X
        USAGE(1), 0x31,       // Y
        USAGE(1), 0x38,       // scroll
        LOGICAL_MINIMUM(1), 0x81, LOGICAL_MAXIMUM(1), 0x7f, INPUT(1), 0x06, // Relative data

        END_COLLECTION(0), END_COLLECTION(0)
    };

    reportLength = sizeof(report_descriptor);
    return report_descriptor;
}

#define DEFAULT_CONFIGURATION (1)
#define TOTAL_DESCRIPTOR_LENGTH ((1 * CONFIGURATION_DESCRIPTOR_LENGTH) \
                               + (1 * INTERFACE_DESCRIPTOR_LENGTH) \
                               + (1 * HID_DESCRIPTOR_LENGTH) \
                               + (2 * ENDPOINT_DESCRIPTOR_LENGTH))

const uint8_t* USBJoystick::configuration_desc(uint8_t index)
{
    if (index != 0)
    {
        return nullptr;
    }

    uint8_t configurationDescriptorTemp[] =
    {
        CONFIGURATION_DESCRIPTOR_LENGTH,    // bLength
        CONFIGURATION_DESCRIPTOR,           // bDescriptorType
        LSB(TOTAL_DESCRIPTOR_LENGTH),       // wTotalLength (LSB)
        MSB(TOTAL_DESCRIPTOR_LENGTH),       // wTotalLength (MSB)
        0x01,                               // bNumInterfaces
        DEFAULT_CONFIGURATION,              // bConfigurationValue
        0x00,                               // iConfiguration
        C_RESERVED | C_SELF_POWERED,        // bmAttributes
        C_POWER(0),                         // bMaxPower

        INTERFACE_DESCRIPTOR_LENGTH,        // bLength
        INTERFACE_DESCRIPTOR,               // bDescriptorType
        0x00,                               // bInterfaceNumber
        0x00,                               // bAlternateSetting
        0x02,                               // bNumEndpoints
        HID_CLASS,                          // bInterfaceClass
        HID_SUBCLASS_BOOT,                  // bInterfaceSubClass
        HID_PROTOCOL_MOUSE,                 // bInterfaceProtocol
        0x00,                               // iInterface

        HID_DESCRIPTOR_LENGTH,              // bLength
        HID_DESCRIPTOR,                     // bDescriptorType
        LSB(HID_VERSION_1_11),              // bcdHID (LSB)
        MSB(HID_VERSION_1_11),              // bcdHID (MSB)
        0x00,                               // bCountryCode
        0x01,                               // bNumDescriptors
        REPORT_DESCRIPTOR,                  // bDescriptorType
        (uint8_t) (LSB(report_desc_length())), // wDescriptorLength (LSB)
        (uint8_t) (MSB(report_desc_length())), // wDescriptorLength (MSB)

        ENDPOINT_DESCRIPTOR_LENGTH,         // bLength
        ENDPOINT_DESCRIPTOR,                // bDescriptorType
        _int_in,                            // bEndpointAddress
        E_INTERRUPT,                        // bmAttributes
        LSB(MAX_HID_REPORT_SIZE),           // wMaxPacketSize (LSB)
        MSB(MAX_HID_REPORT_SIZE),           // wMaxPacketSize (MSB)
        1,                                  // bInterval (milliseconds)

        ENDPOINT_DESCRIPTOR_LENGTH,         // bLength
        ENDPOINT_DESCRIPTOR,                // bDescriptorType
        _int_out,                           // bEndpointAddress
        E_INTERRUPT,                        // bmAttributes
        LSB(MAX_HID_REPORT_SIZE),           // wMaxPacketSize (LSB)
        MSB(MAX_HID_REPORT_SIZE),           // wMaxPacketSize (MSB)
        1                                  // bInterval (milliseconds)
    };

    MBED_ASSERT(sizeof(configurationDescriptorTemp) == sizeof(configurationDescriptor));
    memcpy(configurationDescriptor, configurationDescriptorTemp, sizeof(configurationDescriptor));
    return configurationDescriptor;
}
