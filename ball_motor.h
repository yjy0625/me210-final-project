#ifndef ball_motor_h
#define ball_motor_h

#include "Arduino.h"

class BallMotor {
public:
	BallMotor(int pwmPin, int powerPin1, int powerPin2);
  void start();
  void stop();
private:
  int _pwmPin;
};

#endif