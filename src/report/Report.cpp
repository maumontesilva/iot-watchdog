/*
 * Report.cpp
 *
 *  Created on: 20 Mar 2018
 *      Author: maurosil
 */

#include "Report.h"

Report::Report(std::vector<std::string> memReport, std::vector<std::string> netReport)
{
	memoryReport = memReport;
	networkReport = netReport;
}

std::string Report::generateReport()
{
	std::string report {};
	//TEMPORARY - ONLY TO TEST THE COMMUNICATION USING MQTT
	//ADD PROPERTIES LIKE ID, REPORT_DATE and so on.
	report.append("{\"memoryProcesses\":[");
	for(unsigned int index = 0; index < memoryReport.size(); index++)
	{
		if(index == 0)
		{
			report.append("\"" + memoryReport[index] + "\"");
		}
		else {
			report.append(",\"" + memoryReport[index] + "\"");
		}

	}
	report.append("],");
	report.append("\"networkProcesses\":[");
	for(unsigned int index = 0; index < networkReport.size(); index++)
	{
		if(index == 0)
		{
			report.append("\"" + networkReport[index] + "\"");
		}
		else {
			report.append(",\"" + networkReport[index] + "\"");
		}

	}
	report.append("]}");

	return report;
}
