#ifndef AWS_MQTT_H
#define AWS_MQTT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// AWS IoT credentials
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_topic;
extern char* ca_cert;
extern const char* client_cert;
extern const char* client_key;

void connectAWS();
void publishToAWS(const char* message);

#endif
