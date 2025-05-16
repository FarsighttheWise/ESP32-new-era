#ifndef MEASURED_ID_H
#define MEASURED_ID_H

#include <Arduino.h>

// Initialize the measured_id system (e.g., load counters from EEPROM if needed)
void initMeasuredId();

// Generate a new unique measured_id string for each reading
String generateMeasuredId();

#endif
