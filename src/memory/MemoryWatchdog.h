#include "MonitoringType.h"

#ifndef MEMORYWATCHDOG_H
#define MEMORYWATCHDOG_H

class MemoryWatchdog
{
public:
	MemoryWatchdog();
	std::vector<std::string> getRunningProcesses(MemoryMonitoringType);

};

#endif // MEMORYWATCHDOG_H
