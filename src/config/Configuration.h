#include <iostream>
/*
 * Configuration.h
 *
 *  Created on: 23 Mar 2018
 *      Author: maurosil
 */

#ifndef SRC_CONFIG_CONFIGURATION_H_
#define SRC_CONFIG_CONFIGURATION_H_

class Configuration {
public:
	~Configuration();
	static Configuration* getInstance();

private:
	Configuration();
    static bool instanceFlag;
    static Configuration *instance;
};

#endif /* SRC_CONFIG_CONFIGURATION_H_ */
