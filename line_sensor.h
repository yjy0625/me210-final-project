#ifndef line_sensor_h
#define line_sensor_h

#include <QTRSensors.h>
#include "Arduino.h"


class LineSensor {
public:
	LineSensor();
	uint8_t readLeftValue();
	uint8_t readMidValue();
	uint8_t readRightValue();
private:
	QTRSensors qtr;
	const static uint8_t sensorCount = 3;
	uint16_t sensorValues[sensorCount];
};

#endif