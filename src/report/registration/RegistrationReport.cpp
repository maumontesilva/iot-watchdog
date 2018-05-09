/*
 * RegistrationReport.cpp
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */
#include <chrono>

#include "RegistrationReport.h"

RegistrationReport::RegistrationReport(std::string uuid) {
	iotWatchogAgentUUID = uuid;
}

std::string RegistrationReport::generateReport()
{
	std::string report {};
	std::chrono::system_clock::time_point currentStartTime = std::chrono::system_clock::now();
	std::time_t currentStartEpochTime = std::chrono::system_clock::to_time_t(currentStartTime);

	report.append("{\"iotWatchdogUUID\":\"" + iotWatchogAgentUUID + "\",");
	report.append("\"registrationTime\":\"" + std::string(std::ctime(&currentStartEpochTime)) + "\"}");

	return report;
}

std::string RegistrationReport::getTopic()
{
	return "/cit/msc/iot/watchdog/registration";
}
