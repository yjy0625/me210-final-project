#ifndef proximity_sensor_h
#define proximity_sensor_h

#include "Arduino.h"
#include "TimerInterrupt.hpp"

#define PROXIMITY_SENSOR_OUTPUT_PIN 2
#define PROXIMITY_SENSOR_INPUT_PIN 7

class ProximitySensor {
public:
	ProximitySensor(int outputPin, int inputPin);
  ProximitySensor() : ProximitySensor(PROXIMITY_SENSOR_OUTPUT_PIN, PROXIMITY_SENSOR_INPUT_PIN) {}
  void init(TimerInterrupt &timer);
  float read();
private:
  static int _outputPin, _inputPin;
  static int cnt, on;
  const static int period = 60;
  constexpr static float triggerPulse = 0.00001;
  const static float thres = triggerPulse / 0.06 * 1024;

  static void update();
};

#endif