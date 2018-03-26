# ****** Variable to set the compilation**************************
CXX=g++
CXXFLAGS=-Wall -g -std=c++11
LIB_MOSQUITTO=-lmosquitto
PTHREAD=-pthread
# enable all warning
# -g enable debug
# ****************************************************************

main: iot-watchdog-application.o memory.o network.o report.o sender.o config.o
	$(CXX) $(CXXFLAGS) $(PTHREAD) \
			-o iot-watchdog-application \
				iot-watchdog-application.o \
				memory/MemoryWatchdog.o \
				network/NetworkingWatchdog.o \
				memory/ps/PSMonitoring.o \
				utils/CommandExecutor.o \
				utils/StringHelper.o \
				report/Report.o \
				sender/ReportSender.o $(LIB_MOSQUITTO)

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

report.o:
	$(CXX) $(CXXFLAGS) -c report/Report.cpp -o report/Report.o

sender.o:
	$(CXX) $(CXXFLAGS) -c sender/ReportSender.cpp -o sender/ReportSender.o $(LIB_MOSQUITTO)

config.o:
	$(CXX) $(CXXFLAGS) -c config/Configuration.cpp -o config/Configuration.o

clean:
	rm -f iot-watchdog-application
	rm -f *.o
	rm -f memory/*.o
	rm -f memory/ps/*.o
	rm -f memory/proc/*.o
	rm -f network/*.o
	rm -f utils/*.o
	rm -f report/*.o
	rm -f sender/*.o
	rm -f config/*.o
