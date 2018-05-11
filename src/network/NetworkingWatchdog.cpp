/*
 * NetworkingWatchdog.cpp
 *
 *  Created on: 6 Mar 2018
 *      Author: maurosil
 */

#include "NetworkingWatchdog.h"
#include "netstat/NetstatMonitoring.h"

NetworkingWatchdog::NetworkingWatchdog()
{
}

std::vector<std::string> NetworkingWatchdog::getRunningProcesses()
{
	std::vector<std::string> networkingReport;
	NetstatMonitoring netstatMonitoring;

	networkingReport = netstatMonitoring.run();

	return networkingReport;
}
