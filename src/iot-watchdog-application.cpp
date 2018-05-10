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
#include "report/data/DataReport.h"
#include "report/registration/RegistrationReport.h"
#include "report/reboot/RebootReport.h"
#include "sender/ReportSender.h"
#include "config/Configuration.h"

const std::string USAGE_MESSAGE {"USAGE: ./iot-watchdog-application [-c/--config <config file path>] [-h / --help]"};
const std::string HELP_ARGUMENT = "help";
const std::string CONFIG_FILE_PATH_ARGUMENT = "configFilePath";
const std::string DEFAULT_CONFIG_FILE = "./config.cfg";

void printHelp();
void registerIoTWatchdog(std::string iotWatchogAgentUUID);
void informIoTWatchdogRebbot(std::string iotWatchogAgentUUID);
void validateInputArguments(int argc, char **argv, std::map<std::string, std::string> &arguments);
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
	std::map<std::string, std::string> arguments;
	std::string configFile = DEFAULT_CONFIG_FILE;

	try
	{
		validateInputArguments(argc, argv, arguments);
		if(arguments.count(HELP_ARGUMENT) == 1 && arguments[HELP_ARGUMENT] == "true")
		{
			printHelp();
			exit(0);
		}

		if(arguments.count(CONFIG_FILE_PATH_ARGUMENT) == 1)
		{
			configFile = arguments[CONFIG_FILE_PATH_ARGUMENT];
		}
	} catch(const std::invalid_argument& exception)
	{
		printHelp();
		exit(-1);
	} catch(const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		exit(-2);
	}

	Configuration *config = Configuration::getInstance(configFile);

	if(config->getIoTWatchdogAgentNeedRegistration())
	{
		registerIoTWatchdog(config->getIoTWatchdogAgentUUID());
		config->setIoTWatchdogAgentNeedRegistration(false);
	}

	informIoTWatchdogRebbot(config->getIoTWatchdogAgentUUID());

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

		DataReport dataReport {memoryReport, networkReport, config->getIoTWatchdogAgentUUID()};
		ReportSender sender {};

		sender.sendReport(&dataReport);

		const std::chrono::minutes INTERVAL_PERIOD_MINUTES{config->getHeartbeatInMinutes()};
		NextStartTime = currentStartTime + INTERVAL_PERIOD_MINUTES;
		std::time_t NextStartEpochTime = std::chrono::system_clock::to_time_t(NextStartTime);

		std::cout << "Next Watchdog agent execution is at " << std::ctime(&NextStartEpochTime)  << std::endl;

		std::this_thread::sleep_until(NextStartTime);
	} while(true);
	
	return 0;
}

void validateInputArguments(int argc, char **argv, std::map<std::string, std::string> &arguments)
{
	int count = 1; //First position skipping the program name
	while(count < argc)
	{
		std::string element = argv[count];
		if( (element.compare("-c") == 0 || element.compare("--config") == 0) &&  (count+1) <= argc )
		{
			arguments.insert(std::make_pair(CONFIG_FILE_PATH_ARGUMENT, argv[count+1]));
			count = count +2;
		} else if(element.compare("-h") == 0 || element.compare("--help") == 0)
		{
			arguments.insert(std::make_pair(HELP_ARGUMENT, "true"));
			count++;
		}
		else
		{
			throw std::invalid_argument(USAGE_MESSAGE);
		}
	}
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

void printHelp()
{
	std::cout << "*************************************************************************************************" << std::endl;
	std::cout << "IoT Watchdog agent." << std::endl;
	std::cout << "Project developed by Mauro Monteiro Silva - mauro.silva@mycit.ie" << std::endl;
	std::cout << "This project was created as a thesis project for Information Security master at CIT Cork." << std::endl;
	std::cout << "The IoT Watchdog agent collects, monitors and sends data from IoT device to the IoT hub." << std::endl;
	std::cout << std::endl;
	std::cout << USAGE_MESSAGE << std::endl;
	std::cout << "*************************************************************************************************" << std::endl;
}

void registerIoTWatchdog(std::string iotWatchogAgentUUID)
{
	std::cout << "Registering IoT Watchdog agent ..." << std::endl;

	RegistrationReport registrationReport {iotWatchogAgentUUID};
	ReportSender sender {};

	sender.sendReport(&registrationReport);
}

void informIoTWatchdogRebbot(std::string iotWatchogAgentUUID)
{
	std::cout << "Informing IoT Watchdog agent reboot ..." << std::endl;

	RebootReport rebootReport {iotWatchogAgentUUID};
	ReportSender sender {};

	sender.sendReport(&rebootReport);
}
