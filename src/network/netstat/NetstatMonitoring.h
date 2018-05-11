/*
 * NetstatMonitoring.h
 *
 *  Created on: 11 May 2018
 *      Author: maurosil
 */

#include <string>
#include <vector>

#ifndef SRC_NETWORK_NETSTAT_NETSTATMONITORING_H_
#define SRC_NETWORK_NETSTAT_NETSTATMONITORING_H_

class NetstatMonitoring {
public:
	NetstatMonitoring();

	std::vector<std::string> run();
private:
	std::string parsePSOutput(std::string line);
	std::vector<std::string> processCommand(std::string cmd);

	const char* NETSTAT_COMMAND_TCP;
	const char* NETSTAT_COMMAND_UDP;
	const char* NETSTAT_DELIMITER;
	const char* CVS_DELIMITER;
	const int PROTO_INDEX = 0;
	const int RECV_Q_INDEX = 1;
	const int SEND_Q_INDEX = 2;
	const int LOCAL_ADDRESS_INDEX = 3;
	const int FOREIGN_ADDRESS_INDEX = 4;
	const int STATE_INDEX = 5;
};

#endif /* SRC_NETWORK_NETSTAT_NETSTATMONITORING_H_ */
