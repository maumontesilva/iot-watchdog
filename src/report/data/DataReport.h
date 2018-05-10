/*
 * DataReport.h
 *
 *  Created on: 8 May 2018
 *      Author: maurosil
 */

#ifndef SRC_REPORT_DATA_DATAREPORT_H_
#define SRC_REPORT_DATA_DATAREPORT_H_

#include <vector>
#include <string>

#include "../Report.h"

class DataReport: public Report {
public:
	DataReport(std::vector<std::string> memReport, std::vector<std::string> netReport, std::string uuid);
	std::string generateReport();
	std::string getTopic();

private:
	std::vector<std::string> memoryReport;
	std::vector<std::string> networkReport;
	std::string iotWatchogAgentUUID;
};

#endif /* SRC_REPORT_DATA_DATAREPORT_H_ */
