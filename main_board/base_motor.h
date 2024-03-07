#ifndef base_motor_h
#define base_motor_h

#include "Arduino.h"


#define MOTOR1_PWM_OUT 5
#define MOTOR1_POWER_OUT1 8
#define MOTOR1_POWER_OUT2 9

#define MOTOR2_PWM_OUT 6
#define MOTOR2_POWER_OUT1 12
#define MOTOR2_POWER_OUT2 13

class BaseMotor {
public:
	BaseMotor(int leftEn, int leftIn1, int leftIn2,
            int rightEn, int rightIn1, int rightIn2);
  BaseMotor() : BaseMotor(MOTOR1_PWM_OUT, MOTOR1_POWER_OUT1, MOTOR1_POWER_OUT2,
                            MOTOR2_PWM_OUT, MOTOR2_POWER_OUT1, MOTOR2_POWER_OUT2) {}

  void switchLeftRight();
  
  void moveForward(float v);
  void moveBackward(float v);
  void turnLeft(float v);
  void turnRight(float v);
  void turnLeftPrimitive();
  void turnRightPrimitive();
  void turnLeftSlowPrimitive();
  void turnRightSlowPrimitive();

  void turnLeftFixedBlock();
  void turnRightFixedBlockAgainstContactZone();
  void turnLeftFixedBlockShootingZone();

  void stopAll();
  void setVoltages(float vl, float vr);
private:
  static constexpr int MOTOR_LEFT_DIR = 1;
  static constexpr int MOTOR_RIGHT_DIR = 0;
  static constexpr float MOTOR_SCALE = 1.166;
  static constexpr float EPS = 0.1;
  static constexpr float TURN_SIDE_NEAR_DELTA = -3.0;
  static constexpr float TURN_SIDE_FAR_DELTA = -2.0;
  static constexpr float CONTACT_TURN_TIME = 1420;
  
  int le, l1, l2, re, r1, r2;
  void setLeftVoltage(float v);
  void setRightVoltage(float v);
};

#endif