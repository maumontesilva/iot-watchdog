/*
 * StringHelper.h
 *
 *  Created on: 7 Mar 2018
 *      Author: maurosil
 */
#include <string>
#include <vector>

#ifndef SRC_UTILS_STRINGHELPER_H_
#define SRC_UTILS_STRINGHELPER_H_

class StringHelper {
public:
	StringHelper();

	static std::string replaceAll(std::string str, const std::string& from, const std::string& to);
	static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);
};

#endif /* SRC_UTILS_STRINGHELPER_H_ */
