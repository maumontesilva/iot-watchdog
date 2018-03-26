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

Configuration::~Configuration()
{
	instanceFlag = false;
}

Configuration* Configuration::getInstance()
{
    if(!instanceFlag)
    {
        instance = new Configuration();
        instanceFlag = true;
    }

    return instance;
}
