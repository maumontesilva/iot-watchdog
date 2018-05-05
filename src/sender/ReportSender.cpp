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

#define STATUS_CONNECTING 0
#define STATUS_CONNACK_RECVD 1

// Server connection parameters
//#define MQTT_HOSTNAME "test.mosquitto.org"
#define MQTT_BROKER "192.168.56.101"
#define MQTT_PORT 8883
#define MQTT_TOPIC "/cit/2018/dissertation/report/test"

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
	std::cout << "Connected to " << MQTT_BROKER << std::endl;

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

//void msg_cb(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
//{
//	bool match = 0;
//	printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
//
//	mosquitto_topic_matches_sub("#", message->topic, &match);
//	if (match) {
//		printf("got message for ADC topic\n");
//	}
//
//}

ReportSender::ReportSender()
{
	msgSent = 0;
	int rc = 0;

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

	rc = mosquitto_connect(mosquitoStruct, MQTT_BROKER, MQTT_PORT, 60);
	if(rc)
	{
		std::cout << "Error connecting to: " << MQTT_BROKER << ":" << MQTT_PORT << std::endl;
	}
}


void ReportSender::sendReport(Report report)
{
	std::string reportStr = report.generateReport();

	const char *reportRef = reportStr.c_str();

	std::cout << "sending report with : " << strlen(reportRef) << " characters." << std::endl;

	mosquitto_loop_start(mosquitoStruct);

	do {
		sleep(1);
		if(status == STATUS_CONNACK_RECVD)
		{
			// Publish the message to the topic
		    mosquitto_publish (mosquitoStruct, NULL, MQTT_TOPIC,
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
