/*
 * Alarm.h
 *
 *  Created on: 13.04.2020
 *      Author: marci
 */

#ifndef SOURCE_ALARM_H_
#define SOURCE_ALARM_H_

#include "Console.h"
#include "mbed.h"

enum class AlarmID
{
    I2CWrite,
    I2CWriteBeforeRead,
    I2CReadAfterWrite
};

class Alarm
{
public:
    Alarm();
    void set(AlarmID alarmId);
    void display(CommandVector cv);
    void clear(CommandVector cv);
private:
    uint32_t alarmRegister{0};
    DigitalOut alarmLed;
};

#endif /* SOURCE_ALARM_H_ */
