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
	virtual std::string generateReport() = 0;
	virtual std::string getTopic() = 0;

	virtual ~Report();
};

#endif /* SRC_REPORT_REPORT_H_ */
