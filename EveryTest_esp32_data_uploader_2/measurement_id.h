#ifndef MEASUREMENT_ID_H
#define MEASUREMENT_ID_H

#include <Arduino.h>

class MeasurementID {
public:
    MeasurementID();

    // Call this every time a new sensor reading arrives
    // Returns current measurement_id string
    String get_current_id();

    // Call this to add a sensor reading to current group
    // Automatically moves to next id after 3 readings
    void add_reading();

    // Set the result ("safe" / "unsafe") after 3 readings
    void set_result(const String& result);

    // Get the stored result for the current measurement
    String get_result() const;

private:
    int _current_id;
    int _reading_count;
    String _result;
};

#endif
