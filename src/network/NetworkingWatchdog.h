/*
 * NetworkingWatchdog.h
 *
 *  Created on: 6 Mar 2018
 *      Author: maurosil
 */

#include <string>
#include <vector>

#ifndef NETWORKINGWATCHDOG_H
#define NETWORKINGWATCHDOG_H

class NetworkingWatchdog
{
public:
	NetworkingWatchdog();

	std::vector<std::string> getRunningProcesses();
};

#endif // NETWORKINGWATCHDOG_H
