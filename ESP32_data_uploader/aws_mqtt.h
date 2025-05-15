#ifndef AWS_MQTT_H
#define AWS_MQTT_H

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "certificates.h"
#include <time_module.h>
#include <sensor.h>
#include <ArduinoJson.h>

const char* mqtt_server = "a4cs001g1zepe-ats.iot.us-east-1.amazonaws.com";
const int mqtt_port = 8883;
const char* mqtt_topic = "esp32/data";

void connectAWS(PubSubClient& client, WiFiClientSecure& net, const char* mqtt_server, int mqtt_port, const char* mqtt_topic, const char* ca_cert, const char* client_cert, const char* client_key) {
  net.setCACert(ca_cert);
  net.setCertificate(client_cert);
  net.setPrivateKey(client_key);

  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to AWS!");
    } else {
      Serial.print("Connection failed: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void publishSensorData(PubSubClient& client, const char* mqtt_topic) {
  StaticJsonDocument<256> doc;
  
  // Get sensor readings
  doc["sensor_id"] = "esp32-01";  // Can be dynamic if necessary
  doc["timestamp"] = getTimestamp(); // From time_module
  doc["pH"] = readPH();           // From sensors
  doc["TDS"] = readTDS();         // From sensors
  doc["turbidity"] = readTurbidity();  // From sensors
  doc["result"] = "safe";  // Optional result based on your logic

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  client.publish(mqtt_topic, jsonBuffer);
}

#endif
