#ifndef line_sensor_h
#define line_sensor_h

#include <QTRSensors.h>
#include "Arduino.h"


class LineSensor {
public:
	LineSensor(const int l, const int m, const int r);
	uint8_t readLeftValue();
	uint8_t readMidValue();
	uint8_t readRightValue();
  bool dark(uint8_t v);
  bool light(uint8_t v);
private:
	QTRSensors qtr;
	const static uint8_t sensorCount = 3;
	uint16_t sensorValues[sensorCount];
};

#endif