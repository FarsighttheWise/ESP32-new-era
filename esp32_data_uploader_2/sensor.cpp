#include "sensor.h"

String getTimestamp() {
  unsigned long epochTime = millis() / 1000;  // Get seconds since start of program
  return String(epochTime);  // You can adjust this format as needed
}

void createSensorDataJson(StaticJsonDocument<256>& doc) {
  doc["sensor_id"] = "esp32-01";     // Sensor ID
  doc["timestamp"] = getTimestamp(); // Timestamp
  doc["pH"] = 5.4;                   // pH value
  doc["TDS"] = 440;                  // TDS value
  doc["turbidity"] = 80;             // Turbidity value
  doc["result"] = "safe";            // Calibration result
}
