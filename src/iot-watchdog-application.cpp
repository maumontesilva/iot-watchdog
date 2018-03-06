#include <iostream>

#include "memory/MemoryWatchdog.h"
#include "memory/MonitoringType.h"

const int ONLY_PROGRAM_NAME = 1;

void validateInputArguments(int argc, char **argv);

/*
 * ./iot-watchdog-application [-m psmonitoring | procmonitoring ] [ -h | --help ]
 *
 * psmonitoring: It is the default value for memory monitoring
 *
 */
int main(int argc, char **argv)
{
	try
	{
		validateInputArguments(argc, argv);
	} catch(const std::invalid_argument& exception)
	{
		std::cout << "Error: " << exception.what() << std::endl;
		exit(-1);
	}

	std::cout << "Starting IoT Watchdog agent ..." << std::endl;
	
	MemoryWatchdog memoryWatchdog {};
	
	memoryWatchdog.getRunningProcesses(MemoryMonitoringType::psmonitoring);
	
	std::cout << "Watchdog agent has finished its execution." << std::endl;

	return 0;
}

void validateInputArguments(int argc, char **argv)
{
	if(argc != ONLY_PROGRAM_NAME)
	{
		throw std::invalid_argument("Need to implement parsing arguments!");
	}
}
