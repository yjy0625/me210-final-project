#ifndef base_motor_h
#define base_motor_h

#include "Arduino.h"

class BaseMotor {
public:
	BaseMotor(int leftEn, int leftIn1, int leftIn2,
            int rightEn, int rightIn1, int rightIn2);
  void moveForward(float v);
  void moveBackward(float v);
  void turnLeft(float v);
  void turnRight(float v);
private:
  int le, l1, l2, re, r1, r2;
  void setLeftVoltage(float v);
  void setRightVoltage(float v);
};

#endif