# ****** Variable to set the compilation**************************
CXX=g++
CXXFLAGS=-Wall -g -std=c++11
# enable all warning
# -g enable debug
# ****************************************************************

main: iot-watchdog-application.o memory.o	network.o
	$(CXX) $(CXXFLAGS) -pthread -o iot-watchdog-application \
			iot-watchdog-application.o \
			memory/MemoryWatchdog.o \
			network/NetworkingWatchdog.o \
			memory/ps/PSMonitoring.o \
			utils/CommandExecutor.o \
			utils/StringHelper.o

# Compile the object file only
iot-watchdog-application.o:
	$(CXX) $(CXXFLAGS) -c iot-watchdog-application.cpp

memory.o: ps-monitoring.o
	$(CXX) $(CXXFLAGS) -c memory/MemoryWatchdog.cpp -o memory/MemoryWatchdog.o

network.o:
	$(CXX) $(CXXFLAGS) -c network/NetworkingWatchdog.cpp -o network/NetworkingWatchdog.o

ps-monitoring.o: commandExecutor.o stringHelper.o
	$(CXX) $(CXXFLAGS) -c memory/ps/PSMonitoring.cpp -o memory/ps/PSMonitoring.o

commandExecutor.o:
	$(CXX) $(CXXFLAGS) -c utils/CommandExecutor.cpp -o utils/CommandExecutor.o
	
stringHelper.o:
	$(CXX) $(CXXFLAGS) -c utils/StringHelper.cpp -o utils/StringHelper.o

clean:
	rm -f iot-watchdog-application
	rm -f *.o
	rm -f memory/*.o
	rm -f memory/ps/*.o
	rm -f memory/proc/*.o
	rm -f network/*.o
	rm -f utils/*.o
