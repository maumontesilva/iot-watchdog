/*
 * CommandExecutor.h
 *
 *  Created on: 7 Mar 2018
 *      Author: maurosil
 */
#include <string>

#ifndef SRC_UTILS_COMMANDEXECUTOR_H_
#define SRC_UTILS_COMMANDEXECUTOR_H_

class CommandExecutor {
public:
	CommandExecutor();

	static std::string runCommand(const char* command);
};

#endif /* SRC_UTILS_COMMANDEXECUTOR_H_ */
