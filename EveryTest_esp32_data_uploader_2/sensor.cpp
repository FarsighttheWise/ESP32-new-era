#include "sensor.h"
#include <time.h>

String getTimestamp() {
  // Simulate time starting from Jan 1, 2025 (UTC): 1735689600
  time_t simulatedEpoch = 1735689600 + (millis() / 1000);
  struct tm* timeinfo = gmtime(&simulatedEpoch);

  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
  return String(buf);
}

void createSensorDataJson(StaticJsonDocument<256>& doc) {
  doc["sensor_id"] = "esp32-01";
  doc["timestamp"] = getTimestamp();
  doc["pH"] = 5.4;
  doc["TDS"] = 440;
  doc["turbidity"] = 80;
  doc["result"] = "safe";
}
