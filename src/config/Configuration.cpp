/*
 * Configuration.cpp
 *
 *  Created on: 23 Mar 2018
 *      Author: maurosil
 */

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Configuration.h"

//std::map<std::string, std::string> Configuration::iotWatchdogProperties {};
bool Configuration::instanceFlag = false;
Configuration *Configuration::instance = NULL;

const std::string HEARTBEAT_PERIOD_IN_MINUTES = "heartbeat_period_in_minutes";

int heartbeat_period_in_minutes = 5;
std::string mqtt_broker_host;
int mqtt_broker_port=0;
std::string iot_watchdog_agent_uuid;
bool iot_watchdog_agent_need_registration=true;

Configuration::Configuration(std::string configFile)
{
	std::ifstream configFileStream {configFile};
	if(!configFileStream) throw std::runtime_error("configuration file " + configFile + " not found!");

	std::string line;
	while(configFileStream >> line)
	{
		if(!(line.find("#") == 0))
		{
			int delimeterPostion = line.find("=");
			std::string propertyName = line.substr(0, delimeterPostion);
			std::string propertyValue = line.substr(delimeterPostion+1);

			if(propertyName.compare("heartbeat_period_in_minutes") == 0)
			{
				heartbeat_period_in_minutes = atoi(propertyValue.c_str());
			} else if(propertyName.compare("mqtt_broker_host") == 0)
			{
				mqtt_broker_host = propertyValue;
			} else if(propertyName.compare("mqtt_broker_port") == 0)
			{
				mqtt_broker_port = atoi(propertyValue.c_str());
			} else if(propertyName.compare("iot_watchdog_agent_uuid") == 0)
			{
				iot_watchdog_agent_uuid = propertyValue;
			} else if(propertyName.compare("iot_watchdog_agent_need_registration") == 0)
			{
				iot_watchdog_agent_need_registration = propertyValue.compare("yes") == 0 ? true : false;
			}
		}
	}

	configFileStream.close();

	checkMandantoryProperties();
}

Configuration::~Configuration()
{
	instanceFlag = false;
}

Configuration* Configuration::getInstance(std::string configFile)
{
    if(!instanceFlag)
    {
        instance = new Configuration(configFile);
        instanceFlag = true;
    }

    return instance;
}

Configuration* Configuration::getInstance()
{
	return Configuration::getInstance("");
}

void Configuration::checkMandantoryProperties()
{
	if(mqtt_broker_host.size() == 0
			|| iot_watchdog_agent_uuid.size() == 0 || mqtt_broker_port == 0)
	{
		throw std::invalid_argument("Missing required properties!");
	}
}

int Configuration::getHeartbeatInMinutes()
{
	return heartbeat_period_in_minutes;
}

std::string Configuration::getMQTTBrokerHost()
{
	return mqtt_broker_host;
}

int Configuration::getMQTTBrokerPort()
{
	return mqtt_broker_port;
}

std::string Configuration::getIoTWatchdogAgentCertificate()
{
	return "cert/server.crt";
}

std::string Configuration::getIoTWatchdogAgentUUID()
{
	return iot_watchdog_agent_uuid;
}

bool Configuration::getIoTWatchdogAgentNeedRegistration()
{
	return iot_watchdog_agent_need_registration;
}

void Configuration::setIoTWatchdogAgentNeedRegistration(bool needRegistration)
{
	iot_watchdog_agent_need_registration = needRegistration;
	//persist the change to a file
}
