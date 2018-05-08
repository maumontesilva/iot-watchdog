/*
 * RebootReport.h
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */

#ifndef SRC_REPORT_REBOOT_REBOOTREPORT_H_
#define SRC_REPORT_REBOOT_REBOOTREPORT_H_

#include "../Report.h"

class RebootReport: public Report {
public:
	RebootReport();
	std::string generateReport();
	std::string getTopic();

};

#endif /* SRC_REPORT_REBOOT_REBOOTREPORT_H_ */
