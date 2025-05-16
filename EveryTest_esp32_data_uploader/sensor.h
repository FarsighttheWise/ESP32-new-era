#ifndef SENSOR_H
#define SENSOR_H

#include <ArduinoJson.h>

String getTimestamp();
void createSensorDataJson(StaticJsonDocument<256>& doc);

#endif
