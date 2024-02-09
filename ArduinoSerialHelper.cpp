#include "ArduinoSerialHelper.h"

#ifndef ArduinoSerialHelperDefaultSerialPort
    #define ArduinoSerialHelperDefaultSerialPort   Serial
#endif

#ifndef ArduinoSerialHelperBufferSize
    #define ArduinoSerialHelperBufferSize   128
#endif

static int _timeout = 0;
static HardwareSerial* _serial = &ArduinoSerialHelperDefaultSerialPort;
static char _serialBuffer[ArduinoSerialHelperBufferSize];

void SerialHelperSetSerial(HardwareSerial* serial)
{
    _serial = serial;
}

void SerialHelperSetScanfTimeout(int val)
{
    _timeout = val;
}

int	scanf (const char* format, ...)
{
    int lastChar = 0;
    size_t index = 0;
    unsigned long start = millis();

    while(lastChar != '\n' && index < (sizeof(_serialBuffer) - 1) && (_timeout <= 0 || ((millis() - start) <= _timeout)))
    {
        if(_serial->available())
        {
            lastChar = _serial->read();
            if (lastChar >= 0)
            {
                _serialBuffer[index++] = (char)lastChar;
            }
        }
    }
    _serialBuffer[index] = '\0';

    if (lastChar != '\n')
    {
        return -1;
    }

    va_list args;
    va_start(args, format);
    int matches = vsscanf(_serialBuffer, format, args);
    va_end(args);
    return matches; 
}

int printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int len = vsnprintf(_serialBuffer, sizeof(_serialBuffer), format, args);
    if(len > 0) 
    {
        len = _serial->write((uint8_t*)_serialBuffer, len);
    }
    va_end(args);
    return len;
}
