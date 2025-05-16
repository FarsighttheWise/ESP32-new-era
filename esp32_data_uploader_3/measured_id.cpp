#include "measured_id.h"
#include <EEPROM.h>

const int EEPROM_ADDR = 0;  // Starting EEPROM address for the counter
unsigned long currentCounter = 0;

void initMeasuredId() {
  EEPROM.begin(512);  // Adjust size as needed
  currentCounter = EEPROM.readULong(EEPROM_ADDR);
  if (currentCounter == 0xFFFFFFFF) { // EEPROM empty
    currentCounter = 0;
  }
}

String generateMeasuredId() {
  currentCounter++;
  EEPROM.writeULong(EEPROM_ADDR, currentCounter);
  EEPROM.commit();

  // Format measured_id as a zero-padded 8-digit number string, e.g., "00000001"
  char idStr[10];
  snprintf(idStr, sizeof(idStr), "%08lu", currentCounter);
  return String(idStr);
}
