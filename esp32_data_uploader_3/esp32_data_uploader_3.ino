#include <ArduinoJson.h>
#include "wifi_module.h"
#include "aws_mqtt.h"
#include "sensor.h"

const char* ssid = "UwU";//"Redmi 10";
const char* password = "akubutuhmedkit";//"CloseYourEyes";

int readingCounter = 0; // For measured_id suffix

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectWiFi(ssid, password);

  // Connect to AWS
  connectAWS();
}

void loop() {
  // Display Wi-Fi status
  displayWiFiStatus();

  // Example sensor data for publishing
  StaticJsonDocument<256> doc;  // Increase buffer size if necessary
  createSensorDataJson(doc);

  // Serialize the JSON object to a string
  char jsonBuffer[256];  // Ensure this is large enough for your JSON data
  serializeJson(doc, jsonBuffer);
 
  // Publish the JSON data to AWS
  publishToAWS(jsonBuffer);

  delay(5000);  // Publish every 5 seconds (adjust timing as needed)
}
