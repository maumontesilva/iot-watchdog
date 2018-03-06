#include <iostream>

#include "MemoryWatchdog.h"
#include "MonitoringType.h"
#include "ps/PSMonitoring.h"

MemoryWatchdog::MemoryWatchdog()
{
	
}

void MemoryWatchdog::getRunningProcesses(MemoryMonitoringType memoryMonitoringType)
{
	PSMonitoring a {};

	switch(memoryMonitoringType) {
	case MemoryMonitoringType::psmonitoring:
		a.run();

		break;
	case MemoryMonitoringType::procmonitoring:
	default:
		//memoryMonitoring = procMonitoring();

		std::cout << "Proc monitoring not implemented yet." << std::endl;
	}

	/*
	 * TO DO: USE INHERITANCE TO RUN HERE!
	 */
}
