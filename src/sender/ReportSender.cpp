/*
 * ReportSender.cpp
 *
 *  Created on: 20 Mar 2018
 *      Author: maurosil
 */

#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#include "ReportSender.h"
#include "../config/Configuration.h"

#define STATUS_CONNECTING 0
#define STATUS_CONNACK_RECVD 1

static int status = STATUS_CONNECTING;
static int msgSent = 0;

struct brook_obj {
 unsigned long long published;
 unsigned long long connected;
 unsigned long long disconnected;
 unsigned long long loged;
};

/*
static void log_cb(struct mosquitto *mosq, void *obj, int level, const char *str)
{
	std::cout << "LOG CALLBACK" << std::endl;

// struct brook_obj *bobj = (struct brook_obj*) obj;
// bobj->loged++;
//        printf("%s(), connect:%llu, published:%llu, loged:%llu, level:%d,\n\tstr:%s\n",
//  __FUNCTION__, bobj->connected, bobj->published, bobj->loged, level, str);
}
*/

static void connect_cb(struct mosquitto *mosq, void *obj, int rc)
{
	std::cout << "Connected." << std::endl;

//	struct brook_obj *bobj = (struct brook_obj*) obj;
//	bobj->connected++;
//		printf("%s(), connect:%llu, published:%llu, loged:%llu, rc:%d\n",
//				__FUNCTION__, bobj->connected, bobj->published, bobj->loged, rc);
	if(!rc) {
		status = STATUS_CONNACK_RECVD;
	}
}

static void publish_cb(struct mosquitto *mosq, void *obj, int mid)
{
	std::cout << "Message published." << std::endl;

// struct brook_obj *bobj = (struct brook_obj*) obj;
// bobj->published++;
//        printf("%s(), connect:%llu, published:%llu, loged:%llu, mid:%d\n",
//  __FUNCTION__, bobj->connected, bobj->published, bobj->loged, mid);
}

ReportSender::ReportSender()
{
	msgSent = 0;
	int rc = 0;

	Configuration *config = Configuration::getInstance("");

	mosquitto_lib_init();

	const char *id = "MAURO-PI";
	mosquitoStruct = mosquitto_new (id, true, NULL);
	if(!mosquitoStruct)
	{
		std::cout << "Failed to create mosquitto object." << std::endl;
	}

	mosquitto_connect_callback_set(mosquitoStruct, connect_cb);
	mosquitto_publish_callback_set(mosquitoStruct, publish_cb);

	const char *cafile = "cert/server.crt";
	rc = mosquitto_tls_set(mosquitoStruct, cafile, NULL, NULL, NULL, NULL);
	if(rc)
	{
		std::cout << "Error setting certificate." << std::endl;
	}

	const char *brokerHost = config->getMQTTBrokerHost().c_str();
	const int brokerPort = config->getMQTTBrokerPort();
	rc = mosquitto_connect(mosquitoStruct, brokerHost, brokerPort, 60);
	if(rc)
	{
		std::cout << "Error connecting to: " << brokerHost << ":" << brokerPort << std::endl;
	}
}


void ReportSender::sendReport(Report *report)
{
	std::string reportStr = report->generateReport();
	const char *reportRef = reportStr.c_str();
	std::string topicStr = report->getTopic();
	const char *topic = topicStr.c_str();

	std::cout << "sending report with : " << strlen(reportRef) << " characters." << std::endl;

	mosquitto_loop_start(mosquitoStruct);

	do {
		sleep(1);
		if(status == STATUS_CONNACK_RECVD)
		{
			mosquitto_publish (mosquitoStruct, NULL, topic,
				      strlen(reportRef), reportRef, 0, false);
		    mosquitto_disconnect (mosquitoStruct);
		    msgSent = 1;
		} else {
		    mosquitto_loop(mosquitoStruct, -1, 1);
		}
	} while(!msgSent);

    mosquitto_loop_stop(mosquitoStruct, false);

    mosquitto_destroy (mosquitoStruct);
    mosquitto_lib_cleanup();
}
