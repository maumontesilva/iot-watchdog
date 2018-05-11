/*
 * NetstatMonitoring.h
 *
 *  Created on: 11 May 2018
 *      Author: maurosil
 */

#include "NetstatMonitoring.h"

#include "../../utils/CommandExecutor.h"
#include "../../utils/StringHelper.h"
#include "../../utils/CommandExecutor.h"
#include "../../utils/StringHelper.h"

NetstatMonitoring::NetstatMonitoring() {
	NETSTAT_COMMAND_TCP = "netstat -ant | sed -n '1!p'"; //remove the first line which is a description
	NETSTAT_COMMAND_UDP = "netstat -anu | sed -n '1!p' | sed -n '1!p'"; //remove the first 2 lines, description and header
	NETSTAT_DELIMITER = " ";
	CVS_DELIMITER = ";;;;";
}

std::string NetstatMonitoring::parsePSOutput(std::string line)
{
	std::string result = "";

	std::vector<std::string> tokens =
									StringHelper::splitString(line, NETSTAT_DELIMITER);

	result.append(tokens[PROTO_INDEX] + CVS_DELIMITER);
	result.append(tokens[RECV_Q_INDEX] + CVS_DELIMITER);
	result.append(tokens[SEND_Q_INDEX] + CVS_DELIMITER);
	result.append(tokens[LOCAL_ADDRESS_INDEX] + CVS_DELIMITER);
	result.append(tokens[FOREIGN_ADDRESS_INDEX] + CVS_DELIMITER);
	result.append(tokens[STATE_INDEX]);

	return result;
}

std::vector<std::string> NetstatMonitoring::processCommand(std::string cmd)
{
	std::vector<std::string> output;

	std::string result = CommandExecutor::runCommand(cmd.c_str());
	if(result.size() > 0)
	{
		std::vector<std::string> lines = StringHelper::splitString(result, "\n");
		for(std::string &line : lines)
		{
			if(line.size() > 0)
			{
				std::string netstatAttributes = parsePSOutput(line);

				if(netstatAttributes.size() > 0)
				{
					output.push_back(netstatAttributes);
				}
			}
		}
	}

	return output;
}
std::vector<std::string> NetstatMonitoring::run() {
	std::vector<std::string> cvsReport;
	std::string header;

	cvsReport = processCommand(NETSTAT_COMMAND_TCP);
	std::vector<std::string> temp = processCommand(NETSTAT_COMMAND_UDP);

	cvsReport.insert(std::end(cvsReport), std::begin(temp), std::end(temp));

	return cvsReport;
}
