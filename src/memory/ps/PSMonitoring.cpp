/*
 * PSMonitoring.cpp
 *
 *  Created on: 6 Mar 2018
 *      Author: maurosil
 */
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

#include "PSMonitoring.h"
#include "../../utils/CommandExecutor.h"
#include "../../utils/StringHelper.h"

const int   USER_POSITION 	= 0;
const int   PID_POSITION  	= 1;
const int   START_POSITION  = 8;
const int   TIME_POSITION  	= 9;
const int   CMD_POSITION  	= 10;

const char* PS_COMMAND = "ps -aux";
const char* PS_DELIMITER = " ";
const char* CVS_DELIMITER = ";;;;";

PSMonitoring::PSMonitoring() {}

std::string parsePSOutput(std::string line)
{
	std::string result = "";

	std::vector<std::string> tokens =
									StringHelper::splitString(line, PS_DELIMITER);

	if(tokens.size() >= CMD_POSITION) //expected size of the vector
	{
		std::string pid = tokens[PID_POSITION];
		if(StringHelper::isInt(pid))
		{
			result.append(tokens[USER_POSITION] + CVS_DELIMITER);
			result.append(pid + CVS_DELIMITER);
			result.append(tokens[START_POSITION] + CVS_DELIMITER);
			result.append(tokens[TIME_POSITION] + CVS_DELIMITER);

			std::string cmd = "";
			for(unsigned int index = CMD_POSITION; index < tokens.size(); index++)
			{
				if(cmd == "")
				{
					cmd.append(tokens[index]);
				} else
				{
					cmd.append(" " + tokens[index]);
				}
			}

			result.append(cmd);
		}
	}

	return result;
}

std::vector<std::string> PSMonitoring::run() {
	std::vector<std::string> cvsReport;
	std::string result = CommandExecutor::runCommand(PS_COMMAND);

	if(result.size() > 0)
	{
		std::vector<std::string> lines = StringHelper::splitString(result, "\n");

		for(std::string &line : lines)
		{
			if(line.size() > 0)
			{
				std::string psAttributes = parsePSOutput(line);

				if(psAttributes.size() > 0)
				{
					cvsReport.push_back(psAttributes);
				}
			}
		}
	}

	return cvsReport;
}
