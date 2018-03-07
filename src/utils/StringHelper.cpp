/*
 * StringHelper.cpp
 *
 *  Created on: 7 Mar 2018
 *      Author: maurosil
 */

#include "StringHelper.h"

StringHelper::StringHelper() {
	// TODO Auto-generated constructor stub

}

std::string StringHelper::replaceAll(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }

    return str;
}

std::vector<std::string> StringHelper::splitString(const std::string& str, const std::string& delimiter)
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
