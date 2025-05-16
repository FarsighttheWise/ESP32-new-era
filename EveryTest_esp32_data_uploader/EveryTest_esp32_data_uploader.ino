#include <ArduinoJson.h>
#include "wifi_module.h"
#include "aws_mqtt.h"
#include "sensor.h"

// Use placeholders as requested — do not store actual credentials
const char* ssid = "UwU";
const char* password = "akubutuhmedkit";

int readingCounter = 0; // For measured_id suffix if needed

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow serial to stabilize

  connectWiFi(ssid, password);   // Wi-Fi connection
  connectAWS();                  // Connect to AWS IoT Core
}

void loop() {
  displayWiFiStatus();  // Optional for debugging

  StaticJsonDocument<256> doc;
  createSensorDataJson(doc);  // This calls the simulated timestamp

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);

  publishToAWS(jsonBuffer);  // MQTT publish

  delay(5000);  // Delay between publishes
}
