# ****** Variable to set the compilation**************************
CXX=g++
CXXFLAGS=-Wall -g
# ****************************************************************

main: iot-watchdog-application.o memory.o	network.o
	$(CXX) $(CXXFLAGS) -o iot-watchdog-application iot-watchdog-application.o memory/MemoryWatchdog.o network/NetworkingWatchdog.o memory/ps/PSMonitoring.o

# Compile the object file only
iot-watchdog-application.o:
	$(CXX) $(CXXFLAGS) -c iot-watchdog-application.cpp

memory.o: ps-monitoring.o
	$(CXX) $(CXXFLAGS) -c memory/MemoryWatchdog.cpp -o memory/MemoryWatchdog.o

network.o:
	$(CXX) $(CXXFLAGS) -c network/NetworkingWatchdog.cpp -o network/NetworkingWatchdog.o

ps-monitoring.o:
	$(CXX) $(CXXFLAGS) -c memory/ps/PSMonitoring.cpp -o memory/ps/PSMonitoring.o
	
clean:
	rm -f iot-watchdog-application
	rm -f *.o
	rm -f memory/*.o
	rm -f network/*.o