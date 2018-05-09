/*
 * RebootReport.h
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */

#ifndef SRC_REPORT_REBOOT_REBOOTREPORT_H_
#define SRC_REPORT_REBOOT_REBOOTREPORT_H_

#include <string>

#include "../Report.h"

class RebootReport: public Report {
public:
	RebootReport(std::string uuid);
	std::string generateReport();
	std::string getTopic();

private:
	std::string iotWatchogAgentUUID;
};

#endif /* SRC_REPORT_REBOOT_REBOOTREPORT_H_ */
