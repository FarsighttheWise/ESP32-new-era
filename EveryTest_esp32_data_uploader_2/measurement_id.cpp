#include "measurement_id.h"

MeasurementID::MeasurementID() : _current_id(1), _reading_count(0), _result("") {}

String MeasurementID::get_current_id() {
    return "measurement_" + String(_current_id);
}

void MeasurementID::add_reading() {
    _reading_count++;
    if (_reading_count >= 3) {
        _reading_count = 0;
        _current_id++;
    }
}

void MeasurementID::set_result(const String& result) {
    _result = result;
}

String MeasurementID::get_result() const {
    return _result;
}
