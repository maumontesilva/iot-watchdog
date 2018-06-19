/*
 * Configuration.h
 *
 *  Created on: 23 Mar 2018
 *      Author: maurosil
 */

#include <string>
#include <map>

#ifndef SRC_CONFIG_CONFIGURATION_H_
#define SRC_CONFIG_CONFIGURATION_H_

class Configuration {
public:
	static Configuration* getInstance(std::string configFile);
	static Configuration* getInstance();

	int getHeartbeatInSeconds();
	std::string getMQTTBrokerHost();
	int getMQTTBrokerPort();
	std::string getMQTTBrokerCertificate();
	std::string getIoTWatchdogAgentUUID();
	bool getIoTWatchdogAgentNeedRegistration();
	void setIoTWatchdogAgentNeedRegistration(bool needRegistration);

private:
    static bool instanceFlag;
    static Configuration *instance;

    std::string configFile;
    int heartbeat_period_in_seconds;
    int heartbeat_period;
    std::string heartbeat_period_unit;
    std::string mqtt_broker_host;
    int mqtt_broker_port;
    std::string mqtt_broker_certificate;
    std::string iot_watchdog_agent_uuid;
    bool iot_watchdog_agent_need_registration;

    void checkMandantoryProperties();
    int calculateHeartbeatInSeconds();
    void saveConfigFile();

	Configuration(std::string cfgFile);
	~Configuration();
};

#endif /* SRC_CONFIG_CONFIGURATION_H_ */
