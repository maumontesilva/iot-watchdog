#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <map>

#include "memory/MemoryWatchdog.h"
#include "memory/MonitoringType.h"
#include "report/Report.h"
#include "sender/ReportSender.h"

const std::string USAGE_MESSAGE {"USAGE: ./iot-watchdog-application [-c/--config <config file path>] [-h / --help]"};
const int ONLY_PROGRAM_NAME = 1;
const int HEARTBEAT_PERIOD = 5;

std::map<std::string, std::string> validateInputArguments(int argc, char **argv);
void initiallizeMemoryThread(MemoryMonitoringType memoryMonitoringType, std::promise<std::vector<std::string>> * promiseMemoryObj);
void initiallizeNetworkThread(std::promise<std::vector<std::string>> * promiseNetworkObj);

/*
 * ./iot-watchdog-application [-c <config file path>] | [-m psmonitoring | procmonitoring ] [ -h | --help ]
 *
 * psmonitoring: It is the default value for memory monitoring
 * procmonitoring
 *
 */
int main(int argc, char **argv)
{
	try
	{
		std::map<std::string, std::string> arguments = validateInputArguments(argc, argv);
	} catch(const std::invalid_argument& exception)
	{
		std::cout << "Error: " << exception.what() << std::endl;
		exit(-1);
	}

	std::chrono::system_clock::time_point currentStartTime;
	std::chrono::system_clock::time_point NextStartTime;

	do {
		currentStartTime = std::chrono::system_clock::now();
		std::time_t currentStartEpochTime = std::chrono::system_clock::to_time_t(currentStartTime);

		std::cout << "Starting IoT Watchdog agent at " << std::ctime(&currentStartEpochTime) << std::endl;

		//Setting network promise and future
		std::promise<std::vector<std::string>> promiseNetworkObj;
		std::future<std::vector<std::string>> futureNetworkObj = promiseNetworkObj.get_future();
		std::thread networkThread(initiallizeNetworkThread, &promiseNetworkObj);

		//Setting memory promise and future
		std::promise<std::vector<std::string>> promiseMemoryObj;
		std::future<std::vector<std::string>> futureMemoryObj = promiseMemoryObj.get_future();
		std::thread memoryThread(initiallizeMemoryThread, MemoryMonitoringType::psmonitoring, &promiseMemoryObj);

		auto networkReport = futureNetworkObj.get();
		auto memoryReport = futureMemoryObj.get();

		networkThread.join();
		memoryThread.join();

		Report report {memoryReport, networkReport};
		ReportSender sender {};

		sender.sendReport(report);

		const std::chrono::minutes INTERVAL_PERIOD_MINUTES{HEARTBEAT_PERIOD};
		NextStartTime = currentStartTime + INTERVAL_PERIOD_MINUTES;
		std::time_t NextStartEpochTime = std::chrono::system_clock::to_time_t(NextStartTime);

		std::cout << "Next Watchdog agent execution is at " << std::ctime(&NextStartEpochTime)  << std::endl;

		std::this_thread::sleep_until(NextStartTime);
	} while(true);
	
	return 0;
}

std::map<std::string, std::string> validateInputArguments(int argc, char **argv)
{
	std::map<std::string, std::string> arguments;

	int count = 1; //First position skipping the program name
	while(count < argc)
	{
		std::string element = argv[count];
		if( (element.compare("-c") == 0 || element.compare("--config") == 0) &&  (count+1) <= argc )
		{
			arguments.insert(std::make_pair("configFilePath", argv[count+1]));
			count = count +2;
		} else if(element.compare("-h") == 0 || element.compare("--help") == 0)
		{
			arguments.insert(std::make_pair("help", "true"));
			count++;
		}
		else
		{
			throw std::invalid_argument(USAGE_MESSAGE);
		}
	}

	return arguments;
}

void initiallizeMemoryThread(MemoryMonitoringType memoryMonitoringType, std::promise<std::vector<std::string>> * promiseMemoryObj)
{
	MemoryWatchdog memoryWatchdog {};

	std::vector<std::string> memoryReport = memoryWatchdog.getRunningProcesses(memoryMonitoringType);

	promiseMemoryObj->set_value(memoryReport);
}

void initiallizeNetworkThread(std::promise<std::vector<std::string>> * promiseNetworkObj)
{
	std::vector<std::string> tmp;

	promiseNetworkObj->set_value(tmp);
}
