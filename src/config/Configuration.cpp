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

bool Configuration::instanceFlag = false;
Configuration *Configuration::instance = NULL;

const std::string HEARTBEAT_PERIOD_IN_MINUTES = "heartbeat_period_in_minutes";
const std::string MQTT_BROKER_HOST = "mqtt_broker_host";
const std::string MQTT_BROKER_PORT = "mqtt_broker_port";
const std::string IOT_WATCHDOG_AGENT_UUID = "iot_watchdog_agent_uuid";
const std::string IOT_WATCHDOG_AGENT_NEED_REGISTRATION = "iot_watchdog_agent_need_registration";

std::string configFile;
int heartbeat_period_in_minutes = 5;
std::string mqtt_broker_host;
int mqtt_broker_port=0;
std::string iot_watchdog_agent_uuid;
bool iot_watchdog_agent_need_registration=true;

Configuration::Configuration(std::string cfgFile)
{
	configFile = cfgFile;
	std::ifstream configFileStream {cfgFile};
	if(!configFileStream) throw std::runtime_error("configuration file " + cfgFile + " not found!");

	std::string line;
	while(configFileStream >> line)
	{
		if(!(line.find("#") == 0))
		{
			int delimeterPostion = line.find("=");
			std::string propertyName = line.substr(0, delimeterPostion);
			std::string propertyValue = line.substr(delimeterPostion+1);

			if(propertyName.compare(HEARTBEAT_PERIOD_IN_MINUTES) == 0)
			{
				heartbeat_period_in_minutes = atoi(propertyValue.c_str());
			} else if(propertyName.compare(MQTT_BROKER_HOST) == 0)
			{
				mqtt_broker_host = propertyValue;
			} else if(propertyName.compare(MQTT_BROKER_PORT) == 0)
			{
				mqtt_broker_port = atoi(propertyValue.c_str());
			} else if(propertyName.compare(IOT_WATCHDOG_AGENT_UUID) == 0)
			{
				iot_watchdog_agent_uuid = propertyValue;
			} else if(propertyName.compare(IOT_WATCHDOG_AGENT_NEED_REGISTRATION) == 0)
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

Configuration* Configuration::getInstance(std::string cfgFile)
{
    if(!instanceFlag)
    {
        instance = new Configuration(cfgFile);
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
	saveConfigFile();
}

void Configuration::saveConfigFile()
{
	std::cout << "save new configuration ..." << std::endl;
	std::ofstream configFileStream {configFile};
	if(!configFileStream) throw std::runtime_error("configuration file " + configFile + " not found!");

	configFileStream << HEARTBEAT_PERIOD_IN_MINUTES << "=" << heartbeat_period_in_minutes << std::endl;
	configFileStream << MQTT_BROKER_HOST << "=" << mqtt_broker_host << std::endl;
	configFileStream << MQTT_BROKER_PORT << "=" << mqtt_broker_port << std::endl;
	configFileStream << IOT_WATCHDOG_AGENT_UUID << "=" << iot_watchdog_agent_uuid << std::endl;
	std::string needRegistration = iot_watchdog_agent_need_registration ? "yes" : "no";
	configFileStream << IOT_WATCHDOG_AGENT_NEED_REGISTRATION << "=" << needRegistration << std::endl;

	configFileStream.close();
}
