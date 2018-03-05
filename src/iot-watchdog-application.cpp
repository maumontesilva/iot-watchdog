#include <iostream>
using namespace std;

#include "memory/MemoryWatchdog.h"

int main(int argc, char **argv)
{
	cout << "Starting IoT Watchdog agent ...\n";
	
	MemoryWatchdog memoryWatchdog {};
	
	memoryWatchdog.getRunningProcesses();
	
	return 0;
}
