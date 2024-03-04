#ifndef gyro_h
#define gyro_h

#include "Arduino.h"
#include "TimerInterrupt.hpp"

class Gyro {
public:
	Gyro(TimerInterrupt timer);
  float readAngX();
  float readAngY();
  float readAngZ();

private:
	static int16_t acX, acY, acZ, gyX, gyY, gyZ, temp, gyXOS, gyYOS, gyZOS;
  static float angX, angY, angZ;
  static float dt;
  static void update();
};

#endif