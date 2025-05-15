#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// WiFi Credentials
const char* ssid = "UwU";//"Redmi 10";//"Ngabid";//"RahasiaUmum123@#$";
const char* password = "akubutuhmedkit";//"CloseYourEyes";//"Ali200276_";//"YangTauTauAja200276_";

// AWS IoT Endpoint
const char* mqtt_server = "a4cs001g1zepe-ats.iot.us-east-1.amazonaws.com";
const int mqtt_port = 8883;
const char* mqtt_topic = "esp32/data";

// Certs (paste your own)
char* ca_cert = "-----BEGIN CERTIFICATE-----\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----\n";

const char* client_cert = "-----BEGIN CERTIFICATE-----\n"
"MIIDWTCCAkGgAwIBAgIURogYjE9UPzMLVUvVcYbwF9DjQ1IwDQYJKoZIhvcNAQEL\n"
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDUwOTA2NTAx\n"
"NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAK4s24pQih49Zvob5Ml1\n"
"dAznC9TMKbOg1SrID4+6qZFEbKdn0tp0fuwyn33fhe57mKjJ2POV6WFkvnXnKgpf\n"
"U8sUh/ri+V1NXi56AL+Qc4KAOc4qaYGsyjsoiGe2X7MVZohHJ5QebtLLq5s0J0gj\n"
"KKpeoXWdX/UmgtU8j6mpnfKiFNZEoDX7V9//BNqKst6Uq4xIcMvb7EROKiPj/Eem\n"
"C1JBHT5aW6sZd8pIBRBLAiSUNpV/7BihiOG5AB2HAk9NJMktVjvyMqoYNGd3Hq4G\n"
"zTyPuAHjq+B8d4j+tHOY+oz3Ot/dVKS5HpBJmPvhKFwixTf+R3DOkL3WBX1SCOaP\n"
"Y10CAwEAAaNgMF4wHwYDVR0jBBgwFoAUtShM/XEHtRxyE7KYD90aohb1hAIwHQYD\n"
"VR0OBBYEFH6lJewSstDyd5Fm2rFBPnKNjKjwMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCVL+9tNXsyUDAJ/oBJo6BtDLNs\n"
"RinDSv3VuI6mJPaAT0AJb6pHUm9K9hrOAa4qZtdsR1lYMjVgaVNmD5tzKjR8RAY1\n"
"l6NyZEcuQGEd6rOP7JzdDUoMRBwC46Y7zAAxNc7129EE2AldAFK+M1gulSG50M73\n"
"KIEuS+482ky0TS+uiRHG0pkrmv+VGAEcheUEJ7v7JPaTs60ON9Og/aCoTxmS6cXT\n"
"eAKhEEImsA51uGmZj2nEBGzBlMFEt4qyRzAIN7le+CR7Sg/hBIuDCkoMlc9V6Dml\n"
"OtWK9ZCHo7XeGV1Hty9BSfPor9KhIqWt1ftUlKnqMTLZzVlsQK9WGnMGM0aa\n"
"-----END CERTIFICATE-----\n";

const char* client_key = "-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEowIBAAKCAQEArizbilCKHj1m+hvkyXV0DOcL1Mwps6DVKsgPj7qpkURsp2fS\n"
"2nR+7DKffd+F7nuYqMnY85XpYWS+decqCl9TyxSH+uL5XU1eLnoAv5BzgoA5zipp\n"
"gazKOyiIZ7ZfsxVmiEcnlB5u0surmzQnSCMoql6hdZ1f9SaC1TyPqamd8qIU1kSg\n"
"NftX3/8E2oqy3pSrjEhwy9vsRE4qI+P8R6YLUkEdPlpbqxl3ykgFEEsCJJQ2lX/s\n"
"GKGI4bkAHYcCT00kyS1WO/Iyqhg0Z3cergbNPI+4AeOr4Hx3iP60c5j6jPc6391U\n"
"pLkekEmY++EoXCLFN/5HcM6QvdYFfVII5o9jXQIDAQABAoIBAEkJBFIebZw6kSjF\n"
"c41KlAwpAhwMNFxfT6Ot2mChnCMO9yTHc3IpMWOn4psslIOpDh2Q7klODlvJm9fi\n"
"xA0vZfqdNFvuuzP1kk2Y2SF62ATb8eFShYVbyD1ARNqAbeaxTZpNg/onPL9lqiLd\n"
"nq8wFwhBwCCKikdJC8mQqIkzV8j6nlaPvz6+zAhVkkqAlPiATewoGSgHa5bfxNhS\n"
"+5aL07ZhPkwh+eGSPteT7RtioUJvPQFcZHfbjrh8rkXUDPVgonKQ/1Fl7qbglBlu\n"
"X9WvslwobCkWyJvJwFs2NSgTzhz0ElFoRO1cv4SEGOORmvnHJO9iIQfcndeZkoxr\n"
"AJrkdr0CgYEA5gtgXq/yDnPQIYgvfz2YZ2xNthtf9DKl1CoYRDp0vr24el7ODR/G\n"
"m6sdGMN5xP9cmkLPr+mIdSXton+JWIJ/kek+BosGWEQCqQqnaqu3uEcmfXtoWMAO\n"
"X2PzW9XXfDm2x9Rf6/8zKQr5eJ0b4ZaZJEu8hmaLnRixIX7wLM1EnEsCgYEAwdO/\n"
"+UlROS81GHm0y0QnU+3X0jD3y2hYMm1FzLyEKIlYoINNnPnSwhiHIY3VNegX6kUO\n"
"XFuDn2kA6eBVQljbQCRE9ZZvV2Ct01WPN/aATf+8E/RLL1TC5sqYOLBz1ACaSSrI\n"
"2iQdcKHeYU1yzQ+J/p0QoSJt5inbyk+UoRE5ZfcCgYBfk+h1TsrWIF4gIHIDfrb8\n"
"eW4MNHF4hzaI4Ph2GId63F5yUUNxBnvBH6YWLNlB9QsneIzLvM6aRajm8/A/mvCf\n"
"0fWYSFjZgWBNlYSbeD77zGv8hLKE9T7DeUaaKE3AakY73kwARGagLdQavcPgxW5Z\n"
"OzJX8PEe0yx9Cz2Ej8Bq4wKBgFxEDUWAli6Pf0noXZzJE6OLO8ptzvc/84QFqk1c\n"
"i9i0EMFP37lS3vXQMTtSxeTEV+YH+18RnSVcGbg7Nrq/i5cL7NuvQc8pUXWha+yq\n"
"5ca7bu9cwhGE2sZ8OFv7+xc3NjqQKE5XFMCR/Ub6VCSzOfA/GjRqLEB9Oogiu9C0\n"
"X0tfAoGBAM0hA2icbPBuKa6/RpxSg+xtzi7yA5v3MAcuHzZSIeBlgd4THdZzJbwP\n"
"Z83fo/bUStwaPJpkyJwSftV9ztV3/SjyJMWUJskAYOgqOhNWzaKkc/sSLu1PCmTF\n"
"9Kzwhewvnmi2VW1Hxuk18Z0dFc48hod3JmiNPSKdQnrDn9MYbqLZ\n"
"-----END RSA PRIVATE KEY-----\n";

WiFiClientSecure net;
PubSubClient client(net);

void connectAWS() {
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

// Display Wi-Fi status details
void displayWiFiStatus() {
  Serial.print("WiFi Status: ");
  int status = WiFi.status();
  Serial.println(status);
  switch (status) {
    case WL_IDLE_STATUS:         Serial.println("WL_IDLE_STATUS: WiFi is idle"); break;
    case WL_NO_SSID_AVAIL:       Serial.println("WL_NO_SSID_AVAIL: No SSID available"); break;
    case WL_CONNECTED:           Serial.println("WL_CONNECTED: Connected to WiFi"); break;
    case WL_CONNECT_FAILED:      Serial.println("WL_CONNECT_FAILED: Connection failed"); break;
    case WL_DISCONNECTED:        Serial.println("WL_DISCONNECTED: Disconnected from WiFi"); break;
    default:                     Serial.println("Unknown status");
  }
}

String getTimestamp() {
  // You can use any method to generate the timestamp; here's a simple UTC-based one
  unsigned long epochTime = millis() / 1000;  // Get seconds since start of program
  return String(epochTime);  // You can adjust this format as needed
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    displayWiFiStatus(); // Show Wi-Fi status while connecting
  }

  Serial.println("Connected to WiFi!");
  connectAWS();
}

void loop() {
  // Display Wi-Fi status and details in loop
  displayWiFiStatus();
  
  // Check if we're connected to AWS, if not, reconnect
  if (!client.connected()) {
    connectAWS();
  }

  // Example data for publishing
  StaticJsonDocument<256> doc;  // Increase buffer size if necessary

  // Fill the JSON object with sensor data
  doc["sensor_id"] = "esp32-01";     // Sensor ID
  doc["timestamp"] = "1715600000";   // timestamp
  doc["pH"] = 5.4;                   // pH value
  doc["TDS"] = 440;                  // TDS value
  doc["turbidity"] = 80;             // Turbidity value
  doc["result"] = "safe";            // Calibration result

  // Optionally, add a timestamp if you'd like to track the time of measurement
  doc["timestamp"] = getTimestamp(); // Use your own method for the timestamp

  // Serialize the JSON object to a string
  char jsonBuffer[256];  // Ensure this is large enough for your JSON data
  serializeJson(doc, jsonBuffer);

  // Publish the JSON data to the MQTT topic
  client.publish(mqtt_topic, jsonBuffer);

  delay(5000);  // Publish every 5 seconds (adjust timing as needed)

  // Check for input from Serial Monitor to disconnect
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read command until newline
    command.trim();  // Remove any extra spaces or newline characters
    
    if (command == "disconnect") {
      WiFi.disconnect();
      Serial.println("Wi-Fi Disconnected!");
    }
  }
}
