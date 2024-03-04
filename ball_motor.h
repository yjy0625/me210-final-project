#ifndef ball_motor_h
#define ball_motor_h

#include "Arduino.h"

#define BALL_MOTOR_PWM_OUT 10
#define BALL_MOTOR_POWER_OUT1 9
#define BALL_MOTOR_POWER_OUT2 8

class BallMotor {
public:
	BallMotor(int pwmPin, int powerPin1, int powerPin2);
  BallMotor() : BallMotor(BALL_MOTOR_PWM_OUT, BALL_MOTOR_POWER_OUT1, BALL_MOTOR_POWER_OUT2) {}
  
  void start();
  void stop();
private:
  int _pwmPin;
};

#endif