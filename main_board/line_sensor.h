#ifndef line_sensor_h
#define line_sensor_h

#include <QTRSensors.h>
#include "Arduino.h"

#define FREQ 5

class LineSensor {
public:
	LineSensor();
	struct ControllerConfig {
        double e = 0;
		float freq = FREQ;
        float e_old = 0;
        float dedt = 0;
        float ur = 0;
        float ul = 0;
        float dt = 1.0 / FREQ;
        float kp = 1.067 * 1000;
        float kd = 83;
        float FWSpeed = 6;
    };
	static ControllerConfig controllerConfig;
	void init();
	void lineTrackerHandler();
	uint8_t readValues();
	uint8_t readLeftValue();
	uint8_t readMidValue();
	uint8_t readRightValue();

private:
	QTRSensors qtr;
	const static uint8_t sensorCount = 3;
	uint16_t sensorValues[sensorCount];
	uint16_t sensor_l, sensor_r;
};

#endif