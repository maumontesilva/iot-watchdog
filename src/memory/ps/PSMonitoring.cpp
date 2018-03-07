/*
 * PSMonitoring.cpp
 *
 *  Created on: 6 Mar 2018
 *      Author: maurosil
 */
#include <iostream>
#include <string>
#include <vector>

#include "PSMonitoring.h"
#include "../../utils/CommandExecutor.h"
#include "../../utils/StringHelper.h"

const char* PS_COMMAND = "ps -aux";
const char* PS_DELIMITER = " ";

PSMonitoring::PSMonitoring() {
	// TODO Auto-generated constructor stub
}

std::vector<std::string> parsePSOutput(std::string line)
{
	std::vector<std::string> result;

	std::vector<std::string> tokens =
									StringHelper::splitString(line, PS_DELIMITER);

	if(tokens[0] != "") //User
	{
		result.push_back(tokens[0]);
	}

	if(tokens[1] != "") //PID
	{
		result.push_back(tokens[1]);
	}

	std::string cmd = "";
	for(int index = 10; index < tokens.size(); index++)
	{
		if(cmd == "") {
			cmd.append(tokens[index]);
		} else
		{
			cmd.append(" " + tokens[index]);
		}
	}

	result.push_back(cmd);

	return result;
}

void PSMonitoring::run() {
	std::string line;
	std::string result = CommandExecutor::runCommand(PS_COMMAND);

	if(result != "" && result.size() > 0)
	{
		std::vector<std::string> lines = StringHelper::splitString(result, "\n");

		for(std::string &line : lines)
		{
			std::cout << "Process : " << std::endl;

			std::vector<std::string> psAttributes = parsePSOutput(line);

			for (unsigned int index = 0; index < psAttributes.size(); index++) {
				std::cout << "Index" << index << ": " << psAttributes[index] << std::endl;
			}

			std::cout << std::endl;
		}
	}
}
