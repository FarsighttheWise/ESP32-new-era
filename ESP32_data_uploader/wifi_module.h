#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <WiFi.h>       // Wi-Fi library
#include <wifi_auth.h>  // Include credentials

void connectWiFi(const char* ssid, const char* password);  // Function declaration
void displayWiFiStatus();  // Wi-Fi status display function

#endif
