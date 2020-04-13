/*
 * Alarm.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marci
 */

#include "Alarm.h"

Alarm::Alarm() :
    alarmLed(LED3)
{

}

/*
 * sets a particular alarm
 */
void Alarm::set(AlarmID alarmID)
{
    alarmRegister |= (1 << static_cast<int>(alarmID));
    alarmLed = 1;
}
