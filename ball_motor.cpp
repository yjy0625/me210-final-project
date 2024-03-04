#include "ball_motor.h"


BallMotor::BallMotor(int pwmPin, int powerPin1, int powerPin2) {
  _pwmPin = pwmPin;

  pinMode(pwmPin, OUTPUT);
  pinMode(powerPin1, OUTPUT);
  pinMode(powerPin2, OUTPUT);

  digitalWrite(powerPin1, 1);
  digitalWrite(powerPin2, 0);
}

void BallMotor::start() {
  analogWrite(_pwmPin, 150);
}

void BallMotor::stop() {
  analogWrite(_pwmPin, 0);
}