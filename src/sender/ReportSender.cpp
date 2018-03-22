#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#include "ReportSender.h"

/*
 * ReportSender.cpp
 *
 *  Created on: 20 Mar 2018
 *      Author: maurosil
 */

// Server connection parameters
#define MQTT_HOSTNAME "iot.eclipse.org"
#define MQTT_PORT 1883
#define MQTT_TOPIC "/cit/2018/dissertation/report"

ReportSender::ReportSender()
{
	mosquitto_lib_init();

	// Create a new Mosquitto runtime instance with a random client ID,
	//  and no application-specific callback data.
	mosquitoStruct = mosquitto_new (NULL, true, NULL);
	if (!mosquitoStruct)
	{
	    fprintf (stderr, "Can't initialize Mosquitto library\n");
	    exit (-1);
	}

	// Establish a connection to the MQTT server. Do not use a keep-alive ping
	int ret = mosquitto_connect (mosquitoStruct, MQTT_HOSTNAME, MQTT_PORT, 0);
	if (ret)
	{
	   fprintf (stderr, "Can't connect to Mosquitto server\n");
	   exit (-1);
	}
}


void ReportSender::sendReport(Report report)
{
	std::cout << "sending report with : " << report.generateReport().size() << " lines." << std::endl;

	std::string reportStr = report.generateReport();

//	std::string reportStr {"TEST MAURO"};
	const char *reportRef = reportStr.c_str();

    // Publish the message to the topic
    int ret = mosquitto_publish (mosquitoStruct, NULL, MQTT_TOPIC,
	      strlen(reportRef), reportRef, 0, false);
    if (ret)
    {
	    fprintf (stderr, "Can't publish to Mosquitto server\n");
	    exit (-1);
    }

    // We need a short delay here, to prevent the Mosquitto library being
	//  torn down by the operating system before all the network operations
	//  are finished.
	sleep (2);

	// Tidy up
//	mosquitto_disconnect (mosquitoStruct);
//	mosquitto_destroy (mosquitoStruct);
//	mosquitto_lib_cleanup();
}
