#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <WiFi.h>

void connectWiFi(const char* ssid, const char* password);
void displayWiFiStatus();

#endif
