#include <ArduinoJson.h>
#include "wifi_module.h"
#include "aws_mqtt.h"
#include "sensor.h"
#include "measurement_id.h"  // Include the new measurement_id class

const char* ssid = "UwU";
const char* password = "akubutuhmedkit";

MeasurementID measurement_id;

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWiFi(ssid, password);
  connectAWS();
}

void loop() {
  displayWiFiStatus();

  StaticJsonDocument<256> doc;
  createSensorDataJson(doc);

  // Add measurement_id to JSON payload
  doc["measurement_id"] = measurement_id.get_current_id();

  // Add the calibration result (you may want to call set_result() somewhere appropriate)
  doc["result"] = measurement_id.get_result();

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  Serial.println("Publishing JSON:");
  Serial.println(jsonBuffer);
  publishToAWS(jsonBuffer);

  publishToAWS(jsonBuffer);

  // After publishing a reading, increase reading count
  measurement_id.add_reading();

  delay(5000);
}
