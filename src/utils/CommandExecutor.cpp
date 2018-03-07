/*
 * CommandExecutor.cpp
 *
 *  Created on: 7 Mar 2018
 *      Author: maurosil
 */
#include <iostream>
#include <string>

#include "CommandExecutor.h"

CommandExecutor::CommandExecutor()
{
	// TODO Auto-generated constructor stub
}

std::string CommandExecutor::runCommand(const char* command)
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(command, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);

    return result;
}
