#include <iostream>
#include <string>
#include <vector>

#include "MemoryWatchdog.h"
#include "MonitoringType.h"
#include "ps/PSMonitoring.h"

MemoryWatchdog::MemoryWatchdog()
{
	
}

std::vector<std::string> MemoryWatchdog::getRunningProcesses(MemoryMonitoringType memoryMonitoringType)
{
	std::vector<std::string> memoryReport;

	PSMonitoring a {};

	switch(memoryMonitoringType) {
	case MemoryMonitoringType::psmonitoring:
		memoryReport = a.run();

		break;
	case MemoryMonitoringType::procmonitoring:
	default:
		//memoryMonitoring = procMonitoring();

		std::cout << "Proc monitoring not implemented yet." << std::endl;
	}

	/*
	 * TO DO: USE INHERITANCE TO RUN HERE!
	 */

	return memoryReport;
}
