#include "line_sensor.h"


LineSensor::LineSensor(const int leftPin, const int midPin, const int rightPin) {
  const uint8_t sensorPins[sensorCount] = {leftPin, midPin, rightPin};
	qtr.setTypeRC();
	qtr.setSensorPins(sensorPins, sensorCount);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("[line_sensor.cpp] Line Sensor Calibration Min Values:");
  for (uint8_t i = 0; i < sensorCount; i++) {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  Serial.println("[line_sensor.cpp] Line Sensor Calibration Max Values:");
  for (uint8_t i = 0; i < sensorCount; i++) {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();

  delay(1000);
}


uint8_t LineSensor::readLeftValue() {
	uint16_t position = qtr.readLineBlack(sensorValues);
	return sensorValues[0];
}


uint8_t LineSensor::readMidValue() {
	uint16_t position = qtr.readLineBlack(sensorValues);
	return sensorValues[1];
}


uint8_t LineSensor::readRightValue() {
	uint16_t position = qtr.readLineBlack(sensorValues);
	return sensorValues[2];
}

bool LineSensor::dark(uint8_t v) {
  return v > 600;
}

bool LineSensor::light(uint8_t v) {
  return !dark(v);
}