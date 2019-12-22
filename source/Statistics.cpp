/*
 * Statistics.cpp
 *
 *  Created on: 22.12.2019
 *      Author: Marcin
 */

#include "mbed.h"
#include "mbed_stats.h"
#include "Statistics.h"

#if !defined(MBED_THREAD_STATS_ENABLED)
#error "Stats not enabled"
#endif

void displayThreadStatistics(CommandVector cv)
{

}
