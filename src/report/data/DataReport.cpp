/*
 * DataReport.cpp
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */
#include <chrono>

#include "DataReport.h"

DataReport::DataReport(std::vector<std::string> memReport, std::vector<std::string> netReport, std::string uuid)
{
	memoryReport = memReport;
	networkReport = netReport;
	iotWatchogAgentUUID = uuid;
}

std::string DataReport::generateReport()
{
	std::string report {};
	std::chrono::system_clock::time_point currentStartTime = std::chrono::system_clock::now();
	std::time_t currentStartEpochTime = std::chrono::system_clock::to_time_t(currentStartTime);

	report.append("{\"iotWatchdogUUID\":\"" + iotWatchogAgentUUID + "\",");
	report.append("\"executionTime\":\"" + std::string(std::ctime(&currentStartEpochTime)) + "\",");
	report.append("\"memoryProcesses\":[");
	for(unsigned int index = 0; index < memoryReport.size(); index++)
	{
		if(index == 0)
		{
			report.append("\"" + memoryReport[index] + "\"");
		}
		else {
			report.append(",\"" + memoryReport[index] + "\"");
		}

	}
	report.append("],");
	report.append("\"networkTraffic\":[");
	for(unsigned int index = 0; index < networkReport.size(); index++)
	{
		if(index == 0)
		{
			report.append("\"" + networkReport[index] + "\"");
		}
		else {
			report.append(",\"" + networkReport[index] + "\"");
		}

	}
	report.append("]}");

	return report;
}

std::string DataReport::getTopic()
{
	return "/cit/msc/iot/watchdog/device";
}
