#include "wifi_module.h"
#include <WiFi.h>

void connectWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
}

void displayWiFiStatus() {
  Serial.print("WiFi Status: ");
  int status = WiFi.status();
  Serial.println(status);
  switch (status) {
    case WL_IDLE_STATUS: Serial.println("WL_IDLE_STATUS: WiFi is idle"); break;
    case WL_NO_SSID_AVAIL: Serial.println("WL_NO_SSID_AVAIL: No SSID available"); break;
    case WL_CONNECTED: Serial.println("WL_CONNECTED: Connected to WiFi"); break;
    case WL_CONNECT_FAILED: Serial.println("WL_CONNECT_FAILED: Connection failed"); break;
    case WL_DISCONNECTED: Serial.println("WL_DISCONNECTED: Disconnected from WiFi"); break;
    default: Serial.println("Unknown status");
  }
}
