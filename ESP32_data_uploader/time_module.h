#ifndef TIME_MODULE_H
#define TIME_MODULE_H

#include <time.h>

void initializeTime() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for NTP time...");
  time_t now = time(nullptr);
  while (now < 100000) {
    delay(500);
    now = time(nullptr);
  }
  Serial.println("Time acquired!");
}

String getTimestamp() {
  time_t now = time(nullptr);
  struct tm* timeinfo = gmtime(&now);
  char buffer[25];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", timeinfo);  // ISO8601
  return String(buffer);
}

#endif
