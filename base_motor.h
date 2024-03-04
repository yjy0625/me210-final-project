#ifndef base_motor_h
#define base_motor_h

#include "Arduino.h"

#define MOTOR1_PWM_OUT 10
#define MOTOR1_POWER_OUT1 9
#define MOTOR1_POWER_OUT2 8

#define MOTOR2_PWM_OUT 11
#define MOTOR2_POWER_OUT1 12
#define MOTOR2_POWER_OUT2 13


class BaseMotor {
public:
	BaseMotor(int leftEn, int leftIn1, int leftIn2,
            int rightEn, int rightIn1, int rightIn2);
  BaseMotor() : BaseMotor(MOTOR1_PWM_OUT, MOTOR1_POWER_OUT1, MOTOR1_POWER_OUT2,
                            MOTOR2_PWM_OUT, MOTOR2_POWER_OUT1, MOTOR2_POWER_OUT2) {}
  
  void moveForward(float v);
  void moveBackward(float v);
  void turnLeft(float v);
  void turnRight(float v);
  void stopAll();
private:
  static constexpr int MOTOR_LEFT_DIR = 1;
  static constexpr int MOTOR_RIGHT_DIR = 1;
  static constexpr float MOTOR_SCALE = 1.166;
  static constexpr float EPS = 0.1;
  
  int le, l1, l2, re, r1, r2;
  void setLeftVoltage(float v);
  void setRightVoltage(float v);
};

#endif