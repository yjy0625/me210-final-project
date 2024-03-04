#ifndef proximity_sensor_h
#define proximity_sensor_h

#include "Arduino.h"
#include "TimerInterrupt.hpp"

class ProximitySensor {
public:
	ProximitySensor(int outputPin, int inputPin, TimerInterrupt timer);
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