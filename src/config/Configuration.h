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

	int getHeartbeatInMinutes();
	std::string getMQTTBrokerHost();
	int getMQTTBrokerPort();
	std::string getIoTWatchdogAgentUUID();
	bool getIoTWatchdogAgentNeedRegistration();
	void setIoTWatchdogAgentNeedRegistration(bool needRegistration);

private:
    static bool instanceFlag;
    static Configuration *instance;


    std::string configFile;
    int heartbeat_period_in_minutes;
    std::string mqtt_broker_host;
    int mqtt_broker_port;
    std::string iot_watchdog_agent_uuid;
    bool iot_watchdog_agent_need_registration;

    void checkMandantoryProperties();
    void saveConfigFile();

	Configuration(std::string cfgFile);
	~Configuration();
};

#endif /* SRC_CONFIG_CONFIGURATION_H_ */
