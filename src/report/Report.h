/*
 * Report.h
 *
 *  Created on: 20 Mar 2018
 *      Author: maurosil
 */
#include <vector>
#include <string>

#ifndef SRC_REPORT_REPORT_H_
#define SRC_REPORT_REPORT_H_

class Report {
public:
	Report(std::vector<std::string> memReport, std::vector<std::string> netReport);
	std::string generateReport();

private:
	std::vector<std::string> memoryReport;
	std::vector<std::string> networkReport;
};

#endif /* SRC_REPORT_REPORT_H_ */
