#include <mosquitto.h>
#include "../report/Report.h"

/*
 * ReportSender.h
 *
 *  Created on: 20 Mar 2018
 *      Author: maurosil
 */

#ifndef SRC_SENDER_REPORTSENDER_H_
#define SRC_SENDER_REPORTSENDER_H_

class ReportSender {
public:
	ReportSender();

	void sendReport(Report report);
private:
	struct mosquitto *mosquitoStruct = NULL;
};

#endif /* SRC_SENDER_REPORTSENDER_H_ */
