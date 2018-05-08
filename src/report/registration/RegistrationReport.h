/*
 * RegistrationReport.h
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */

#ifndef SRC_REPORT_REBOOT_REGISTRATIONREPORT_H_
#define SRC_REPORT_REBOOT_REGISTRATIONREPORT_H_

#include "../Report.h"

class RegistrationReport: public Report {
public:
	RegistrationReport();
	std::string generateReport();
	std::string getTopic();

};

#endif /* SRC_REPORT_REBOOT_REGISTRATIONREPORT_H_ */
