/*
 * Configuration.cpp
 *
 *  Created on: 23 Mar 2018
 *      Author: maurosil
 */

#include "Configuration.h"

bool Configuration::instanceFlag = false;
Configuration *Configuration::instance = NULL;

Configuration::Configuration()
{

}

Configuration::Configuration(std::string configFile)
{

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

void Configuration::setProperty(std::string name, std::string value)
{
	std::cout << "setProperty test name : " << name << " value: " << value << std::endl;
}
