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

const std::string HEARTBEAT_PERIOD = "heartbeat_period";
const std::string HEARTBEAT_PERIOD_UNIT = "heartbeat_period_unit";
const std::string MQTT_BROKER_HOST = "mqtt_broker_host";
const std::string MQTT_BROKER_PORT = "mqtt_broker_port";
const std::string MQTT_BROKER_CERTIFICATE = "mqtt_broker_certificate";
const std::string IOT_WATCHDOG_AGENT_UUID = "iot_watchdog_agent_uuid";
const std::string IOT_WATCHDOG_AGENT_NEED_REGISTRATION = "iot_watchdog_agent_need_registration";

Configuration::Configuration(std::string cfgFile)
{
	heartbeat_period_in_seconds = 0;
	configFile = cfgFile;
	heartbeat_period = 5;
	heartbeat_period_unit = "";
	mqtt_broker_host = "";
	mqtt_broker_port=0;
	mqtt_broker_certificate = std::string("cert/server.crt");
	iot_watchdog_agent_uuid = "";
	iot_watchdog_agent_need_registration=true;

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

			if(propertyName.compare(HEARTBEAT_PERIOD) == 0)
			{
				heartbeat_period = atoi(propertyValue.c_str());
			} else if(propertyName.compare(HEARTBEAT_PERIOD_UNIT) == 0)
			{
				heartbeat_period_unit = propertyValue;
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
			} else if(propertyName.compare(MQTT_BROKER_CERTIFICATE) == 0)
			{
				mqtt_broker_certificate = propertyValue;
			}
		}
	}

	configFileStream.close();

	checkMandantoryProperties();

	heartbeat_period_in_seconds = calculateHeartbeatInSeconds();
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
			|| iot_watchdog_agent_uuid.size() == 0
			|| mqtt_broker_port == 0)
	{
		throw std::invalid_argument("Missing required properties!");
	}
}

int Configuration::calculateHeartbeatInSeconds()
{
	int result;

	if(heartbeat_period_unit.compare("hours") == 0)
	{
		result = heartbeat_period * 60 * 60;
	} else if(heartbeat_period_unit.compare("minutes") == 0) {
		result = heartbeat_period * 60;
	} else { //seconds
		result = heartbeat_period;
	}

	return result;
}

int Configuration::getHeartbeatInSeconds()
{
	return heartbeat_period_in_seconds;
}

std::string Configuration::getMQTTBrokerHost()
{
	return mqtt_broker_host;
}

int Configuration::getMQTTBrokerPort()
{
	return mqtt_broker_port;
}

std::string Configuration::getMQTTBrokerCertificate()
{
	return mqtt_broker_certificate;
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

	configFileStream << HEARTBEAT_PERIOD << "=" << heartbeat_period << std::endl;
	configFileStream << HEARTBEAT_PERIOD_UNIT << "=" << heartbeat_period_unit << std::endl;
	configFileStream << MQTT_BROKER_HOST << "=" << mqtt_broker_host << std::endl;
	configFileStream << MQTT_BROKER_PORT << "=" << mqtt_broker_port << std::endl;
	configFileStream << MQTT_BROKER_CERTIFICATE << "=" << mqtt_broker_certificate << std::endl;
	configFileStream << IOT_WATCHDOG_AGENT_UUID << "=" << iot_watchdog_agent_uuid << std::endl;
	std::string needRegistration = iot_watchdog_agent_need_registration ? "yes" : "no";
	configFileStream << IOT_WATCHDOG_AGENT_NEED_REGISTRATION << "=" << needRegistration << std::endl;

	configFileStream.close();
}
