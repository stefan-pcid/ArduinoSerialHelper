#ifndef ARDUINO_SERIAL_HELPER
#define ARDUINO_SERIAL_HELPER

#include <Arduino.h>

/// @brief Override the default serial port (default: Serial)
/// @param serial
void SerialHelperSetSerial(HardwareSerial* serial);

/// @brief Set the read timeout (default: infinite)
/// @param val time in milliseconds, 0 or less for infinite wait
void SerialHelperSetScanfTimeout(int val);

#endif