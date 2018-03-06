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

const char* PS_COMMAND = "ps -aux";

PSMonitoring::PSMonitoring() {
	// TODO Auto-generated constructor stub
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
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

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{
    std::vector<std::string> strings;
    std::string token;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
    	token = str.substr(prev, pos - prev);
    	if(token != "") //Considering multiple token in a row
    	{
            strings.push_back(token);
    	}
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

void PSMonitoring::run() {
	std::string line;
	std::string result = exec(PS_COMMAND);

	auto lines = split_string(result, "\n");
	line = lines[12];
	std::cout << "line: \n" << line << std::endl;
	std::string newLine = replaceAll(line, " ", "#");
	std::cout << "newLine: \n" << newLine << std::endl;
	auto characters = split_string(newLine, "#");
	std::cout << "User : " << characters[0] << std::endl;
	std::cout << "Length : " << characters.size() << std::endl;
	for (unsigned int index = 0; index < characters.size(); index++) {
		std::cout << "Index" << index << ": " << characters[index] << std::endl;
	}
}
