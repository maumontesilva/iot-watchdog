/*
 * RebootReport.cpp
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */

#include "RebootReport.h"

RebootReport::RebootReport() {

}

std::string RebootReport::generateReport()
{
	return "";
}

std::string RebootReport::getTopic()
{
	return "/cit/msc/iot/watchdog/reboot";
}
