#include <iostream>
using namespace std;

#include <stdexcept>
#include <stdio.h>
#include <string>

#include <vector>

#include "MemoryWatchdog.h"

MemoryWatchdog::MemoryWatchdog()
{
	
}

MemoryWatchdog::~MemoryWatchdog()
{

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
 
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
 
    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));
 
    return strings;
}

void MemoryWatchdog::getRunningProcesses()
{
	cout << "get running processes ... \n";
	string line;
	string result = exec("ps -aux");
	
	auto lines = split_string(result, "\n");
	line = lines[6];
	cout << "line: \n" << line << "\n";
	string newLine = replaceAll(line, " ", "#");
	newLine = replaceAll(newLine, "?", "MAU");
	cout << "newLine: \n" << newLine << "\n";
	auto characters = split_string(newLine, "#");
	cout << "User : " << characters[0] << "\n";
	cout << "Length : " << sizeof(characters) << "\n";
	for(unsigned int index = 0; index < sizeof(characters); index++)
	{
		cout << "Index" << index << ": " << characters[index] << "\n";	
	}
}