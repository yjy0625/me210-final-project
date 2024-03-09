#include "line_sensor.h"

#define config controllerConfig

LineSensor::ControllerConfig LineSensor::controllerConfig;

LineSensor::LineSensor() {}

void LineSensor::init() {
	qtr.setTypeRC();
	qtr.setSensorPins((const uint8_t[]){10,4,3}, sensorCount);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	for (uint16_t i = 0; i < 500; i++) {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);

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

uint8_t LineSensor::readValues() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  sensor_l = sensorValues[0];
  sensor_m = sensorValues[1];
  sensor_r = sensorValues[2];
}

uint16_t LineSensor::getMax() {
  return max(sensor_l, max(sensor_m, sensor_r));
}

void LineSensor::lineTrackerHandler() {
  if(flip) {
    config.e = ((int)sensor_r - (int)sensor_l) * 0.001 / 300;
  }
  else {
    config.e = ((int)sensor_l - (int)sensor_r) * 0.001 / 300;
  }
  config.dedt = (config.e - config.e_old) / config.dt;
  config.ul = -(config.e * config.kp + config.dedt * config.kd) + config.FWSpeed; 
  config.ur = (config.e * config.kp + config.dedt * config.kd) + config.FWSpeed; 
  config.e_old = config.e; 

  // Print everything to debug
  /*
  // Serial.print("Sensor L: ");
  // Serial.println(sensor_l);
  // Serial.print("Sensor R: ");
  // Serial.println(sensor_r);
  // Serial.print("e: ");
  // Serial.println(config.e);
  // Serial.print("dedt: ");
  // Serial.println(config.dedt);
  // Serial.print("ul: ");
  // Serial.println(config.ul);
  // Serial.print("ur: ");
  // Serial.println(config.ur);
  // Serial.println();
  */

}